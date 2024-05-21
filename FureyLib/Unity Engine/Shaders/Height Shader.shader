
// Height Map Shader
// by Kyle Furey

Shader "Custom/HeightShader"
{
    Properties
    {
        _Color ("Color", Color) = (1,1,1,1)
        _MainTex ("(RGB)", 2D) = "white" {}
        _ProjectionDirection ("Direction", float) = 1
        _ProjectionOffset ("Offset", float) = 0
        _ProjectionHeight ("Projection Height", float) = 1
        _ProjectionRange ("Projection Padding", float) = 0.05
    }
    SubShader
    {
        Tags { "RenderType"="Opaque" }
        LOD 200

        CGPROGRAM
        // Physically based Standard lighting model, and enable shadows on all light types
        #pragma surface surf Standard fullforwardshadows

        // Use shader model 3.0 target, to get nicer looking lighting
        #pragma target 3.0

        sampler2D _MainTex;

        struct Input
        {
            float2 uv_MainTex;
            float3 worldPos;
        };

        fixed4 _Color;
        half _ProjectionDirection;
        half _ProjectionOffset;
        half _ProjectionRange;
        half _ProjectionHeight;

        /*
        // Add instancing support for this shader. You need to check 'Enable Instancing' on materials that use the shader.
        // See https://docs.unity3d.com/Manual/GPUInstancing.html for more information about instancing.
        // #pragma instancing_options assumeuniformscaling
        UNITY_INSTANCING_BUFFER_START(Props)
            // put more per-instance properties here
        UNITY_INSTANCING_BUFFER_END(Props)
        */

        void surf (Input IN, inout SurfaceOutputStandard o)
        {
            // Albedo comes from a texture tinted by color
            float height = tex2D (_MainTex, IN.uv_MainTex).r * _ProjectionHeight;
            float heightDist;
            
            // Y (default)
            if (_ProjectionDirection == 1)
            {
                heightDist = height - (IN.worldPos.x + _ProjectionOffset);
            }
            // X
            else if (_ProjectionDirection == 0)
            {
                heightDist = height - (IN.worldPos.y + _ProjectionOffset);
            }
            // Z
            else
            {
                heightDist = height - (IN.worldPos.z + _ProjectionOffset);
            }

            clip(_ProjectionRange - abs(heightDist));
            o.Albedo = float3(0, 0, 0);
            o.Emission = _Color;
            o.Alpha = 1;
        }
        ENDCG
    }
    FallBack "Diffuse"
}
