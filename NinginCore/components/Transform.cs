using System;

namespace NinginCore
{
    public class Transform
    {
        internal IntPtr transform;

        internal Transform() {} //Internal so Transform can only be created by engine functions

        public Vector3 Position
        {
            get
            {
                InternalCalls.TransformGetPosition(this.transform, out Vector3 result);
                return result;
            }

            set
            {
                InternalCalls.TransformSetPosition(this.transform, ref value);
            }
        }

        public Vector3 Rotation
        {
            get
            {
                InternalCalls.TransformGetRotation(this.transform, out Vector3 result);
                return result;
            }

            set
            {
                InternalCalls.TransformSetPosition(this.transform, ref value);
            }
        }

        public Vector3 Scale
        {
            get
            {
                InternalCalls.TransformGetScale(this.transform, out Vector3 result);
                return result;
            }

            set
            {
                InternalCalls.TransformSetPosition(this.transform, ref value);
            }
        }

        public override string ToString()
        {
            InternalCalls.MonoTransformToString(this.transform, out string result);
            return result;
        }
    }
}
