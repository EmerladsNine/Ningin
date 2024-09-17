namespace NinginCore
{
    public struct Transform
    {
        public Vector3 position
        {
            get
            {
                InternalCalls.TransformGetPosition(ref this, out Vector3 result);
                return result;
            }

            set
            {
                InternalCalls.TransformSetPosition(ref this, ref value);
            }
        }

        public Vector3 rotation
        {
            get
            {
                InternalCalls.TransformGetRotation(ref this, out Vector3 result);
                return result;
            }

            set
            {
                InternalCalls.TransformSetPosition(ref this, ref value);
            }
        }

        public Vector3 scale
        {
            get
            {
                InternalCalls.TransformGetScale(ref this, out Vector3 result);
                return result;
            }

            set
            {
                InternalCalls.TransformSetPosition(ref this, ref value);
            }
        }
    }
}
