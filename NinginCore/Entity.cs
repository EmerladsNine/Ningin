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

        public Transform transform
        {
            get
            {
                InternalCalls.EntityGetTransform(entityId, out IntPtr transformResult);
                Transform transform = new Transform
                {
                    data = transformResult
                };
                return transform;
            }

            set
            {
                InternalCalls.EntitySetTransform(entityId, value.data);
            }
        }
    }
}
