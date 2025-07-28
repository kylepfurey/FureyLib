-- .lua
-- Name
-- Creator


-- TABLE

--- Template table script.
Table = {}
Table.__index = Table


-- TABLE CONSTRUCTORS

--- Default constructor.
function Table:new (x, y)
    local instance = {
        --- Example x variable.
        x = x,

        --- Example y variable
        y = y,

        -- New variables here
    }
    setmetatable(instance, Table)
    return instance
end

-- New constructors here


-- TABLE METHODS

--- Returns the magnitude of this table.
function Table:magnitude()
    if self.x == 0.0 and self.y == 0.0 then
        return 0.0
    end
    return math.sqrt(self.x * self.x + self.y * self.y)
end

--- Normalizes this table.
function Table:normalize()
    local magnitude = self:magnitude()
    if magnitude == 0.0 then
        return self
    end
    self.x = self.x / magnitude
    self.y = self.y / magnitude
    return self
end

-- New methods here
