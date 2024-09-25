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

        public Transform transform
        {
            get
            {
                Transform transform = new Transform();
                InternalCalls.EntityGetTransform(entityId, out IntPtr transformResult);
                transform.transform = transformResult;
                return transform;
            }

            set
            {
                InternalCalls.EntitySetTransform(entityId, value.transform);
            }
        }
    }
}
