// .hpp
// Object Table Type
// by Kyle Furey

#pragma once
#include <string>
#include <unordered_map>
#include <utility>
#include <stdexcept>
#include <typeinfo>


// TO STRING

namespace std {
    /** Standard string to_string() implementation. */
	template<typename T>
    static basic_string<T> to_string(const basic_string<T> &__val) {
        return __val;
    }
}


// TABLE

/** A collection of named objects of any type. */
class table final {
public:

    // OBJECT

    /** A generic, type safe object of any type. */
    class object {
    public:

        // DESTRUCTOR

        /** Destructor. */
        virtual ~object() = default;


        // OBJECT

        /** Returns the type of this object. */
        virtual const std::type_info &type() const = 0;

        /** Returns whether this object is the given type. */
        template <typename T>
        bool is() const {
            return type() == typeid(T);
        }

        /** Casts this object to a reference of the given type. */
        template <typename T>
        T &as() {
            if (type() != typeid(T)) {
                throw std::runtime_error(std::string("ERROR: Casting table object of type ") + type().name() + " to type " + typeid(T).name() + '!');
            }
            return static_cast<templated_object<T> *>(this)->get();
        }

        /** Casts this object to a reference of the given type. */
        template <typename T>
        const T &as() const {
            if (type() != typeid(T)) {
                throw std::runtime_error(std::string("ERROR: Casting table object of type ") + type().name() + " to type " + typeid(T).name() + '!');
            }
            return static_cast<templated_object<T> *>(this)->get();
        }
        
        /** Returns a shallow copy of this object. This new object must be deleted! */
        virtual object *copy() const = 0;
        
        /** Converts this object into a string. */
        virtual std::string to_string() const = 0;
    };

private:

    // TEMPLATED OBJECT

    /** A templated, type safe object of any type. */
    template <typename T>
    class templated_object final : public object {

        // DATA

        /** The underlying data within this object. */
        T data;

    public:

        // CONSTRUCTORS

        /** Default constructor. */
        templated_object() : data() {
        }

        /** Argument constructor. */
        template <typename... A>
        explicit templated_object(A &&...args) : data(std::forward<A>(args)...) {
        }


        // TEMPLATED OBJECT

        /** Returns the type of this object. */
        const std::type_info &type() const override {
            return typeid(T);
        }

        /** Returns a reference to the underlying data within this object. */
        T &get() {
            return data;
        }

        /** Returns a constant reference to the underlying data within this object. */
        const T &get() const {
            return data;
        }
        
        /** Returns a shallow copy of this object. This new object must be deleted! */
        object *copy() const override {
            return new templated_object<T>(data);
        }
        
        /** Converts this object into a string. */
        std::string to_string() const override {
            return std::to_string(data);
        }
    };


    // DATA

    /** Each stored object by name. */
    std::unordered_map<std::string, object *> objects;

public:

    // CONSTRUCTORS AND DESTRUCTOR

    /** Default constructor. */
    table(const size_t buckets = 16) : objects(buckets) {
    }

    /** Copy constructor. */
    table(const table &copied) : objects(copied.objects.bucket_count()) {
        for (auto &pair : copied.objects) {
            objects[pair.first] = pair.second->copy();
        }
    }

    /** Move constructor. */
    table(table &&moved) noexcept : objects(std::move(moved.objects)) {
        moved.objects.clear();
    }

    /** Destructor. */
    ~table() {
        for (auto &pair : objects) {
            delete pair.second;
        }
    }


    // OPERATORS

    /** Copy assignment operator. */
    table &operator=(const table &copied) {
        if (this != &copied) {
            objects.clear();
            for (auto &pair : copied.objects) {
                objects[pair.first] = pair.second->copy();
            }
        }
        return *this;
    }

    /** Move assignment operator. */
    table &operator=(table &&moved) noexcept {
        if (this != &moved) {
            for (auto &pair : objects) {
                delete pair.second;
            }
            objects = std::move(moved.objects);
            moved.objects.clear();
        }
        return *this;
    }

    /** Returns a reference to an object with the given name. */
    object &operator[](const std::string &name) {
        if (!objects.count(name)) {
            throw std::runtime_error(std::string("ERROR: Object of name ") + name + " was not found in the table!");
        }
        return *objects.at(name);
    }

    /** Returns a reference to an object with the given name. */
    const object &operator[](const std::string &name) const {
        if (!objects.count(name)) {
            throw std::runtime_error(std::string("ERROR: Object of name ") + name + " was not found in the table!");
        }
        return *objects.at(name);
    }


    // TABLE

    /** Returns an iterator to the beginning of the table. */
    auto begin() {
        return objects.begin();
    }

    /** Returns an iterator to the end of the table. */
    auto end() {
        return objects.end();
    }

    /** Returns an iterator to the beginning of the table. */
    auto begin() const {
        return objects.begin();
    }

    /** Returns an iterator to the end of the table. */
    auto end() const {
        return objects.end();
    }

    /** Returns the current number of stored objects. */
    size_t size() const {
        return objects.size();
    }

    /** Returns the current number of buckets. */
    size_t buckets() const {
        return objects.bucket_count();
    }

    /** Returns a pointer to the object with the given name and type (or nullptr). */
    template <typename T>
    T *find(const std::string &name) {
        try {
            if (objects.count(name)) {
                return &(objects.at(name)->as<T>());
            }
            return nullptr;
        }
        catch (const std::exception &e) {
            return nullptr;
        }
    }

    /** Returns a pointer to the object with the given name and type (or nullptr). */
    template <typename T>
    const T *find(const std::string &name) const {
        try {
            if (objects.count(name)) {
                return &(objects.at(name)->as<T>());
            }
            return nullptr;
        }
        catch (const std::exception &e) {
            return nullptr;
        }
    }

    /** Returns whether the table contains an object of the given name. */
    bool contains(const std::string &name) const {
        return objects.count(name);
    }

    /** Returns whether the table contains an object of the given name and type. */
    template <typename T>
    bool contains(const std::string &name) const {
        return objects.count(name) && objects.at(name)->is<T>();
    }

    /** Constructs a new object with the given name and type. */
    template <typename T, typename... A>
    T &insert(const std::string &name, A &&...args) {
        if (objects.count(name)) {
            if (!objects[name]->is<T>()) {
                throw std::runtime_error(std::string("ERROR: Overwriting table object of name ") + name + " and type " + objects[name]->type().name() + " with a new object of type " + typeid(T).name() + '!');
            }
            delete objects[name];
        }
        objects[name] = new templated_object<T>(std::forward<A>(args)...);
        return objects[name]->as<T>();
    }

    /** Erases the object with the given name. */
    bool erase(const std::string &name) {
        if (!objects.count(name)) {
            return false;
        }
        delete objects[name];
        objects.erase(name);
        return true;
    }

    /** Clears the table of all its objects. */
    void clear() {
        for (auto &pair : objects) {
            delete pair.second;
        }
        objects.clear();
    }

    /** Converts this table into a string. */
    std::string to_string(const bool pretty_print = true) const {
        if (objects.size() == 0) {
            return "{}";
        }
        std::string json("{");
        if (pretty_print) {
            for (auto &pair : objects) {
                json += "\n\t\"" + pair.first + "\" : " + ((pair.second->is<std::string>()) ? ('"' + pair.second->to_string() + '"') : (pair.second->to_string())) + ',';
            }
            json = json.erase(json.length() - 1, 1);
            json += '\n';
        }
        else {
            for (auto &pair : objects)
            {
                json += " \"" + pair.first + "\" : " + ((pair.second->is<std::string>()) ? ('"' + pair.second->to_string() + '"') : (pair.second->to_string())) + ',';
            }
            json = json.erase(json.length() - 1, 1);
            json += ' ';
        }
        return json + '}';
    }
};
