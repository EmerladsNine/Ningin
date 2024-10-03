using System;

namespace NinginCore
{
    public class Transform : Component
    {

        public Vector3 Position
        {
            get
            {
                InternalCalls.TransformGetPosition(this.data, out Vector3 result);
                return result;
            }

            set
            {
                InternalCalls.TransformSetPosition(this.data, ref value);
            }
        }

        public Vector3 Rotation
        {
            get
            {
                InternalCalls.TransformGetRotation(this.data, out Vector3 result);
                return result;
            }

            set
            {
                InternalCalls.TransformSetRotation(this.data, ref value);
            }
        }

        public Vector3 Scale
        {
            get
            {
                InternalCalls.TransformGetScale(this.data, out Vector3 result);
                return result;
            }

            set
            {
                InternalCalls.TransformSetScale(this.data, ref value);
            }
        }

        public override string ToString()
        {
            InternalCalls.MonoTransformToString(this.data, out string result);
            return result;
        }
    }
}
