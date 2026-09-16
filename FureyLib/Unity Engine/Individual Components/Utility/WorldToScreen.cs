// .cs
// World to Screen UI Library
// by Kyle Furey

using UnityEngine;

/// <summary>
/// Utility functions for mapping positions, bounds, and transforms from world-space to screen-space.
/// </summary>
public static class WorldToScreen
{
    // POINT

    /// <summary>
    /// Returns whether the given world-space position is in view of the main camera.
    /// </summary>
    public static bool IsPointVisible(Vector3 position) => IsPointVisible(
        position,
        Camera.main,
        new Vector2(0.1f, 0.1f),
        new Vector2(0.9f, 0.9f)
    );

    /// <summary>
    /// Returns whether the given world-space position is in view of a specified camera.
    /// </summary>
    public static bool IsPointVisible(Vector3 position, Camera camera, Vector2 bottomLeft, Vector2 topRight)
    {
        Vector3 viewport = camera.WorldToViewportPoint(position);
        return viewport.z > camera.nearClipPlane &&
               viewport.x >= bottomLeft.x && viewport.x <= topRight.x &&
               viewport.y >= bottomLeft.y && viewport.y <= topRight.y;
    }


    // BOX

    /// <summary>
    /// Returns whether any part of the given world-space bounds are in view of the main camera.
    /// </summary>
    public static bool IsBoxVisible(Bounds bounds) => IsBoxVisible(
        bounds,
        Camera.main,
        new Vector2(0.1f, 0.1f),
        new Vector2(0.9f, 0.9f)
    );

    /// <summary>
    /// Returns whether any part of the given world-space bounds are in view of a specified camera.
    /// </summary>
    public static bool IsBoxVisible(Bounds bounds, Camera camera, Vector2 bottomLeft, Vector2 topRight)
    {
        Vector3 bMin = bounds.min;
        Vector3 bMax = bounds.max;
        Vector3[] corner = new Vector3[8];
        corner[0] = bMin;                                               // -X -Y -Z
        corner[1] = bMin; corner[1].x = bMax.x;                         // +X -Y -Z
        corner[2] = bMin; corner[2].z = bMax.z;                         // -X -Y +Z
        corner[3] = bMin; corner[3].x = bMax.x; corner[3].z = bMax.z;   // +X -Y +Z
        corner[4] = bMax;                                               // +X +Y +Z
        corner[5] = bMax; corner[5].x = bMin.x;                         // -X +Y +Z
        corner[6] = bMax; corner[6].z = bMin.z;                         // +X +Y -Z
        corner[7] = bMax; corner[7].x = bMin.x; corner[7].z = bMin.z;   // -X +Y -Z

        Vector2 min = new Vector2(float.MaxValue, float.MaxValue);
        Vector2 max = new Vector2(float.MinValue, float.MinValue);
        bool visible = false;
        for (int i = 0; i < corner.Length; ++i)
        {
            Vector3 viewport = camera.WorldToViewportPoint(corner[i]);
            if (viewport.z <= camera.nearClipPlane)
                continue;
            visible = true;
            min.x = Mathf.Min(min.x, viewport.x);
            max.x = Mathf.Max(max.x, viewport.x);
            min.y = Mathf.Min(min.y, viewport.y);
            max.y = Mathf.Max(max.y, viewport.y);
        }

        if (!visible)
            return false;
        return max.x >= bottomLeft.x && min.x <= topRight.x &&
               max.y >= bottomLeft.y && min.y <= topRight.y;
    }


    // FULL BOX

    /// <summary>
    /// Returns whether all parts of the given world-space bounds are in view of the main camera.
    /// </summary>
    public static bool IsBoxFullyVisible(Bounds bounds) => IsBoxFullyVisible(
        bounds,
        Camera.main,
        new Vector2(0.1f, 0.1f),
        new Vector2(0.9f, 0.9f)
    );

    /// <summary>
    /// Returns whether all parts of the given world-space bounds are in view of a specified camera.
    /// </summary>
    public static bool IsBoxFullyVisible(Bounds bounds, Camera camera, Vector2 bottomLeft, Vector2 topRight)
    {
        Vector3 bMin = bounds.min;
        Vector3 bMax = bounds.max;
        Vector3[] corner = new Vector3[8];
        corner[0] = bMin;                                               // -X -Y -Z
        corner[1] = bMin; corner[1].x = bMax.x;                         // +X -Y -Z
        corner[2] = bMin; corner[2].z = bMax.z;                         // -X -Y +Z
        corner[3] = bMin; corner[3].x = bMax.x; corner[3].z = bMax.z;   // +X -Y +Z
        corner[4] = bMax;                                               // +X +Y +Z
        corner[5] = bMax; corner[5].x = bMin.x;                         // -X +Y +Z
        corner[6] = bMax; corner[6].z = bMin.z;                         // +X +Y -Z
        corner[7] = bMax; corner[7].x = bMin.x; corner[7].z = bMin.z;   // -X +Y -Z

        return IsPointVisible(corner[0], camera, bottomLeft, topRight) &&
               IsPointVisible(corner[1], camera, bottomLeft, topRight) &&
               IsPointVisible(corner[2], camera, bottomLeft, topRight) &&
               IsPointVisible(corner[3], camera, bottomLeft, topRight) &&
               IsPointVisible(corner[4], camera, bottomLeft, topRight) &&
               IsPointVisible(corner[5], camera, bottomLeft, topRight) &&
               IsPointVisible(corner[6], camera, bottomLeft, topRight) &&
               IsPointVisible(corner[7], camera, bottomLeft, topRight);
    }


    // MOVE

    /// <summary>
    /// Adjusts the given target transform to the given world-space position using the main camera's viewport.
    /// </summary>
    public static void FitTransform(Transform target, Bounds bounds, Vector3 position, float cameraOffset) => FitTransform(
        target,
        bounds,
        position,
        cameraOffset,
        Camera.main,
        new Vector2(0.1f, 0.1f),
        new Vector2(0.9f, 0.9f)
    );

    /// <summary>
    /// Adjusts the given target transform to the given world-space position given a camera's viewport and an offset.
    /// </summary>
    public static void FitTransform(Transform target, Bounds bounds, Vector3 position, float cameraOffset, Camera camera, Vector2 bottomLeft, Vector2 topRight)
    {
        Vector3 bMin = bounds.min;
        Vector3 bMax = bounds.max;
        Vector3 offsetFromCenter = position - bounds.center;
        Vector3[] corner = new Vector3[8];
        corner[0] = bMin;                                               // -X -Y -Z
        corner[1] = bMin; corner[1].x = bMax.x;                         // +X -Y -Z
        corner[2] = bMin; corner[2].z = bMax.z;                         // -X -Y +Z
        corner[3] = bMin; corner[3].x = bMax.x; corner[3].z = bMax.z;   // +X -Y +Z
        corner[4] = bMax;                                               // +X +Y +Z
        corner[5] = bMax; corner[5].x = bMin.x;                         // -X +Y +Z
        corner[6] = bMax; corner[6].z = bMin.z;                         // +X +Y -Z
        corner[7] = bMax; corner[7].x = bMin.x; corner[7].z = bMin.z;   // -X +Y -Z

        Vector3 centerViewport = camera.WorldToViewportPoint(position);

        Vector2 minOffset = Vector2.zero;
        Vector2 maxOffset = Vector2.zero;
        for (int i = 0; i < corner.Length; ++i)
        {
            Vector3 cornerWorld = corner[i] + offsetFromCenter;
            Vector3 cornerViewport = camera.WorldToViewportPoint(cornerWorld);
            Vector2 delta = new Vector2(cornerViewport.x - centerViewport.x, cornerViewport.y - centerViewport.y);
            minOffset.x = Mathf.Min(minOffset.x, delta.x);
            maxOffset.x = Mathf.Max(maxOffset.x, delta.x);
            minOffset.y = Mathf.Min(minOffset.y, delta.y);
            maxOffset.y = Mathf.Max(maxOffset.y, delta.y);
        }

        Vector2 clampedBottomLeft = new Vector2(bottomLeft.x - minOffset.x, bottomLeft.y - minOffset.y);
        Vector2 clampedTopRight = new Vector2(topRight.x - maxOffset.x, topRight.y - maxOffset.y);
        if (clampedBottomLeft.x > clampedTopRight.x)
            clampedBottomLeft.x = clampedTopRight.x = (bottomLeft.x + topRight.x) * 0.5f;
        if (clampedBottomLeft.y > clampedTopRight.y)
            clampedBottomLeft.y = clampedTopRight.y = (bottomLeft.y + topRight.y) * 0.5f;

        Vector3 viewport = camera.WorldToViewportPoint(position);
        bool visible = viewport.z > camera.nearClipPlane &&
                       viewport.x >= clampedBottomLeft.x && viewport.x <= clampedTopRight.x &&
                       viewport.y >= clampedBottomLeft.y && viewport.y <= clampedTopRight.y;

        Vector3 finalPosition;
        if (visible)
        {
            target.position = position;
            finalPosition = target.position;
            target.position = new Vector3(finalPosition.x, finalPosition.y, position.z);
        }
        else
        {
            Vector2 center = new Vector2(0.5f, 0.5f);
            Vector2 direction = new Vector2(viewport.x - center.x, viewport.y - center.y).normalized;

            float directionX = direction.x > 0.0f ?
                  (clampedTopRight.x - center.x) / direction.x :
                  (clampedBottomLeft.x - center.x) / direction.x;
            float directionY = direction.y > 0.0f ?
                  (clampedTopRight.y - center.y) / direction.y :
                  (clampedBottomLeft.y - center.y) / direction.y;

            float edge = Mathf.Min(Mathf.Abs(directionX), Mathf.Abs(directionY));
            Vector2 point = center + direction * edge;

            target.position = camera.ViewportToWorldPoint(new Vector3(point.x, point.y, viewport.z));
            finalPosition = target.position;
            target.position = new Vector3(finalPosition.x, finalPosition.y, position.z);
        }

        Vector3 cameraDirection = (finalPosition - camera.transform.position).normalized;
        target.position = camera.transform.position + cameraDirection * cameraOffset;
    }
}
