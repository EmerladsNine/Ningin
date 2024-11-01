using System;

namespace NinginCore
{
    public class Entity
    {
        public readonly ulong entityId;

        protected Entity()
        {
            entityId = 0;
        }

        internal Entity(ulong entityId)
        {
            this.entityId = entityId;
        }

        public bool HasComponent<T>() where T : Component
        {
            return InternalCalls.EntityHasComponent(this.entityId,typeof(T));
        }

        public T GetComponent<T>() where T : Component , new()
        {
            T component = new T();
            InternalCalls.EntityGetComponent(this.entityId,typeof (T),out IntPtr data);
            component.data = data;
            return component;
        }

        private Transform _transform = null;
        public Transform transform
        {
            get
            {
                if (_transform == null)
                {
                    InternalCalls.EntityGetComponent(entityId, typeof(Transform), out IntPtr transformResult);
                    _transform = new Transform
                    {
                        data = transformResult
                    };
                }
                return _transform;
            }
        }
    }
}
