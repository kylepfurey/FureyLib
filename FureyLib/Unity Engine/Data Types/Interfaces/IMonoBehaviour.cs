using System;
using System.Collections;
using System.Collections.Generic;
using System.Threading;

namespace UnityEngine
{
    public interface IObject
    {
        HideFlags hideFlags { get; set; }
        string name { get; set; }
        EntityId GetEntityId();
        int GetInstanceID();
    }

    public interface IComponent : IObject
    {
        Transform transform { get; }
        TransformHandle transformHandle { get; }
        GameObject gameObject { get; }
        string tag { get; set; }
        Component GetComponent(Type type);
        T GetComponent<T>();
        bool TryGetComponent(Type type, out Component component);
        bool TryGetComponent<T>(out T component);
        Component GetComponent(string type);
        Component GetComponentInChildren(Type t, bool includeInactive);
        Component GetComponentInChildren(Type t);
        T GetComponentInChildren<T>(bool includeInactive = false);
        T GetComponentInChildren<T>();
        Component[] GetComponentsInChildren(Type t, bool includeInactive);
        Component[] GetComponentsInChildren(Type t);
        T[] GetComponentsInChildren<T>(bool includeInactive);
        void GetComponentsInChildren<T>(bool includeInactive, List<T> result);
        T[] GetComponentsInChildren<T>();
        void GetComponentsInChildren<T>(List<T> results);
        Component GetComponentInParent(Type t, bool includeInactive);
        Component GetComponentInParent(Type t);
        T GetComponentInParent<T>(bool includeInactive = false);
        T GetComponentInParent<T>();
        Component[] GetComponentsInParent(Type t, bool includeInactive = false);
        Component[] GetComponentsInParent(Type t);
        T[] GetComponentsInParent<T>(bool includeInactive);
        void GetComponentsInParent<T>(bool includeInactive, List<T> results);
        T[] GetComponentsInParent<T>();
        Component[] GetComponents(Type type);
        void GetComponents(Type type, List<Component> results);
        void GetComponents<T>(List<T> results);
        T[] GetComponents<T>();
        int GetComponentIndex();
        bool CompareTag(string tag);
        bool CompareTag(TagHandle tag);
        void SendMessageUpwards(string methodName, object value = null, SendMessageOptions options = SendMessageOptions.RequireReceiver);
        void SendMessageUpwards(string methodName, object value);
        void SendMessageUpwards(string methodName);
        void SendMessageUpwards(string methodName, SendMessageOptions options);
        void SendMessage(string methodName, object value);
        void SendMessage(string methodName);
        void SendMessage(string methodName, object value, SendMessageOptions options);
        void SendMessage(string methodName, SendMessageOptions options);
        void BroadcastMessage(string methodName, object parameter);
        void BroadcastMessage(string methodName);
        void BroadcastMessage(string methodName, SendMessageOptions options);
    }

    public interface IBehaviour : IComponent
    {
        bool enabled { get; set; }
        bool isActiveAndEnabled { get; }
    }

    public interface IMonoBehaviour : IBehaviour
    {
        CancellationToken destroyCancellationToken { get; }
        bool useGUILayout { get; set; }
        bool didStart { get; }
        bool didAwake { get; }
        bool runInEditMode { get; set; }
        bool IsInvoking();
        void CancelInvoke();
        void Invoke(string methodName, float time);
        void InvokeRepeating(string methodName, float time, float repeatRate);
        void CancelInvoke(string methodName);
        bool IsInvoking(string methodName);
        Coroutine StartCoroutine(string methodName);
        Coroutine StartCoroutine(string methodName, object value = null);
        Coroutine StartCoroutine(IEnumerator routine);
        void StopCoroutine(IEnumerator routine);
        void StopCoroutine(Coroutine routine);
        void StopCoroutine(string methodName);
        void StopAllCoroutines();
    }
}
