
// IMEF Repository Functions Script
// Translated by Kyle Furey for NASA VR Project

using System;
using System.Collections.Generic;
using UnityEngine;
using static UnityEngine.Mathf;
using static UnityEngine.Vector3;

// Include this heading to use the class
using static IMEF;

/// <summary>
/// IMEF repository functions translated from Python to C#.
/// </summary>
public static class IMEF
{
    // bfields.py

    /// <summary>
    /// Compute Earth's dipole magnetic field at given cartesian coordinates.
    /// </summary>
    /// <param name="coords">coords (list): array of cartesian coordinates (x, y, z) in units [m]</param>
    /// <param name="sph">sph (bool, optional):  deterimes if input coordinates are in cartesian (False) or spherical (True); Defaults to False.</param>
    /// <returns>float: value of dipole field in units [T] or [kg*s^-2*A^-1]</returns>
    public static Vector3 BDipole(Vector3 coords, bool sph = false)
    {
        Vector3 r;
        float phi;

        if (sph)
        {
            // Unpack coordinates
            var rdir = coords.x;
            var theta = coords.y;
            phi = coords.z;

            // Convert spherical to cartesian coordinates
            var x = rdir * Sin(theta) * Cos(phi);
            var y = rdir * Sin(theta) * Sin(phi);
            var z = rdir * Cos(theta);

            r = new Vector3(x, y, z);
        }
        else
        {
            r = coords;
        }

        // Tilt of magnetic axis [rad]
        phi = Deg2Rad * 11.7f;

        // Magnetic moment of earth [A*m^2]
        var mu = -7.94e22f * new Vector3(0, Sin(phi), Cos(phi));

        // mu_0 [N*A−2] /4*PI
        var M0 = 1.0e-7;

        var rmag = Sqrt(Dot(coords, coords));

        // Calculating dipole field
        var Bdip = (float)M0 * (3.0f * r * Dot(mu, r) / (Pow(rmag, 5)) - mu / (Pow(rmag, 3)));
        return Bdip;
    }


    // efields.py

    /// <summary>
    /// Calculate last closed equipotential (LCE).
    /// </summary>
    /// <returns>From Matsui et al.: In order to calculate such contours, we first search for maximum potential in the radial direction at a fixed MLT value, and then get the minimum of these maximum potentials in the whole MLT range.</returns>
    public static float GetLCE(float[] phidat, ref float[][] udat, float[][] pgrid, int dr)
    {
        // List to hold maximum potential at every MLT
        List<float> umax = new List<float>();

        // Find all coordinate locations at a fixed phi/MLT value, phi[N]
        for (int i = 0; i <= dr; i++)
        {
            var phi_loc = new Tuple<List<int>, List<int>>(new List<int>(), new List<int>());

            // Equivalent to np.where()
            for (int j = 0; j < pgrid.Length; j++)
            {
                if (phidat[j] == pgrid[i][j])
                {
                    phi_loc.Item1.Add(j);
                    phi_loc.Item2.Add(i);
                }
            }

            List<float> uvals = new List<float>();

            for (int j = 0; j <= dr; j++)
            {
                // Find locations where phi[N] exists
                var c1 = phi_loc.Item1[j];
                var c2 = phi_loc.Item2[j];

                // Find all potential values at phi[N]
                uvals.Add(udat[c1][c2]);
            }

            // Find maximum potential
            umax.Add(Max(uvals.ToArray()));
        }

        // Compute minimum of max potentials in the whole MLT range
        var LCE = Min(umax.ToArray());
        return LCE;
    }

    /// <summary>
    /// Compute corotation electric field in equatorial plane from given coordinates.
    /// </summary>
    /// <param name="coords">coords (ndarray): array of coordinates to compute efield in (x,y,z) or (r, theta, phi), with units in [m]; see 'sph' condition.</param>
    /// <param name="sph">sph (bool, optional): deterimes if input coordinates are in cartesian (False) or spherical (True); Defaults to False.</param>
    /// <returns>ndarray: coration E-field in 3 dimensions in units [mV/m]</returns>
    public static Vector3 CorotationEField(Vector3 coords, bool sph = false)
    {
        float rgeo;

        if (sph == false)
        {
            // Convert cartesian to spherical coordinates
            rgeo = CrtToSph(coords[0], coords[1], coords[2]).x;
        }
        else
        {
            // Unpack coordinates
            rgeo = coords[0];
        }

        // Equatorial magnetic field strength at surface of Earth [T]
        var BE = 3.1e-5;

        // Engular velocity of the Earth’s rotation [rad/s]
        var omega = 7.2921e-5;

        // Equatorial radius of earth [m]
        var RE = 6371000;

        // Radial component with zero check
        var ER0 = (omega * BE * Pow(RE, 3)) / Pow(rgeo, 2);

        // Convert to [mV/m]
        ER0 *= 1000;

        // Return array [mV/m]
        var ER = -1 * new Vector3((float)ER0, 0, 0);
        return ER;
    }

    /// <summary>
    /// Compute corotation potential field in equatorial plane from given coordinates.
    /// </summary>
    /// <param name="coords">coords (ndarray): array of coordinates to compute efield in (x,y,z) or (r, theta, phi), with units in [m]; see 'sph' condition.</param>
    /// <param name="sph">sph (bool, optional): deterimes if input coordinates are in cartesian (False) or spherical (True); Defaults to False.</param>
    /// <returns>ndarray: magnitude of corotation potential in units [kV]</returns>
    public static double CorotationPotential(Vector3 coords, bool sph = false)
    {
        float rgeo;

        if (sph == false)
        {
            // Convert cartesian to spherical coordinates
            rgeo = CrtToSph(coords[0], coords[1], coords[2]).x;
        }
        else
        {
            // Unpack coordinates
            rgeo = coords[0];
        }

        // Equatorial magnetic field strength at surface of Earth [T]
        var BE = 3.1e-5;

        // Angular velocity of the Earth’s rotation [rad/s]
        var omega = 7.2921e-5;

        // Equatorial radius of earth [m]
        var RE = 6371000;

        // Calculate potential [V]
        var UR = (omega * Pow(RE, 3) * BE) / rgeo;

        // Return in units [kV]
        return UR * 1e-3;
    }

    /// <summary>
    /// Compute uniform convection electric field strength in equatorial plane in [kV/m^2] with given kp index. Based on Maynard and Chen 1975 (doi:10.1029/JA080i007p01009).
    /// </summary>
    /// <param name="kp">kp (float): kp index</param>
    /// <returns>float: A0; convection electric field strength in [mV/m^2]</returns>
    public static double ConvectionFieldA0(float kp)
    {
        // Equatorial radius of earth [m]
        var RE = 6371000;

        // Uniform convection electric field strength in equatorial plane [kV/m^2]
        var A0 = 0.045 / ((1 - (0.159 * kp) + (Pow(0.0093f * (Pow(kp, 2)), 3))) * (Pow(RE, 2)));

        // Convert to [mV/m^2]
        A0 *= 1e6;

        return A0;
    }

    /// <summary>
    /// Compute Volland-Stern potential field. Model based on Volland 1973 (doi:10.1029/JA078i001p00171) and Stern 1975 (doi:10.1029/JA080i004p00595).
    /// </summary>
    /// <param name="coords">coords (ndarray): array of coordinates to compute efield in (x,y,z) or (r, theta, phi), with units in [m]; see 'sph' condition.</param>
    /// <param name="gs">gs (float): shielding constant</param>
    /// <param name="kp">kp (float): kp index</param>
    /// <param name="sph">sph (bool, optional): deterimes if input coordinates are in cartesian (False) or spherical (True); Defaults to False.</param>
    /// <returns>float: potential in units [kV]</returns>
    public static double VSPotential(Vector3 coords, float gs, float kp, bool sph = false)
    {
        float rgeo;
        float phi;

        if (sph == false)
        {
            // Convert cartesian to spherical coordinates
            var vec = CrtToSph(coords[0], coords[1], coords[2]);
            rgeo = vec.x;
            phi = vec.z;
        }
        else
        {
            // Unpack coordinates
            rgeo = coords[0];
            phi = coords[2];
        }

        // Uniform convection electric field strength in equatorial plane [mV/m^2]
        var A0 = ConvectionFieldA0(kp);

        // VS potential [mV]
        // 5/24/23 - might need to fix, add -92.4 component
        var U = -A0 * Pow(rgeo, gs) * Sin(phi);

        // Return potential in [kv]
        return -U * 1e-6;
    }

    /// <summary>
    /// Compute Volland-Stern conevction electric field.
    /// </summary>
    /// <param name="coords">coords (ndarray): array of coordinates to compute efield in (x,y,z) or (r, theta, phi), with units in [m]; see 'sph' condition.</param>
    /// <param name="gs">gs (float): shielding constant</param>
    /// <param name="kp">kp (float): kp index</param>
    /// <param name="sph">sph (bool, optional): deterimes if input coordinates are in cartesian (False) or spherical (True); Defaults to False.</param>
    /// <returns>ndarray: volland-stern field in 3 dimensions in units [mV/m].</returns>
    public static Vector3 VSEField(Vector3 coords, float gs, float kp, bool sph = false)
    {
        float rgeo;
        float theta;
        float phi;

        if (sph == false)
        {
            // Convert cartesian to spherical coordinates
            var vec = CrtToSph(coords[0], coords[1], coords[2]);
            rgeo = vec.x;
            theta = vec.y;
            phi = vec.z;
        }
        else
        {
            // Unpack coordinates
            rgeo = coords[0];
            theta = coords[1];
            phi = coords[2];
        }

        // Uniform convection electric field strength in equatorial plane [mV/m^2]
        var A0 = ConvectionFieldA0(kp);

        // Radial componenet [mV/m]
        var EC0 = (-92.4 / Pow(rgeo, 2)) - (A0 * gs * (Pow(rgeo, (gs - 1))) * (Sin(phi)));

        // Polar component [mV/m]
        var EC1 = 0.0f;

        // Azimuthal component [mV/m]
        var EC2 = A0 * (Pow(rgeo, (gs - 1))) * (1 / (Sin(theta))) * (Cos(phi));

        // Return array [mV/m]
        var EC = new Vector3((float)EC0, EC1, (float)EC2);

        return EC;
    }


    // boris.py

    /// <summary>
    /// Compute magnitude of vector.
    /// </summary>
    /// <param name="vec"></param>
    /// <returns></returns>
    public static float Mag(Vector3 vec)
    {
        var magnitude = Sqrt(Dot(vec, vec));
        return magnitude;
    }

    /// <summary>
    /// Convert cartesian to spherical coordinates/
    /// </summary>
    /// <param name="x">x -> r : radial distance</param>
    /// <param name="y">y -> theta : polar angle (radians)</param>
    /// <param name="z">z -> phi : azimuthal angle (radians)</param>
    /// <returns>(x, y, z) to (r, theta, phi)</returns>
    public static Vector3 CrtToSph(float x, float y, float z)
    {
        var r = Sqrt(x * x + y * y + z * z);
        var theta = Acos(z / r);
        var phi = Atan2(y, x);

        return new Vector3(r, theta, phi);
    }

    /// <summary>
    /// Convert spherical to cartesian coordinates.
    /// </summary>
    /// <param name="r">r -> x : radial distance</param>
    /// <param name="theta">theta -> y : polar angle (radians)</param>
    /// <param name="phi">phi -> z : azimuthal angle (radians)</param>
    /// <returns>(r, theta, phi) to (x,y,z)</returns>
    public static Vector3 SphToCrt(float r, float theta, float phi)
    {
        var x = r * Sin(theta) * Cos(phi);
        var y = r * Sin(theta) * Sin(phi);
        var z = r * Cos(theta);

        return new Vector3(x, y, z);
    }

    /// <summary>
    /// Boris particle pusher tracing code.
    /// </summary>
    /// <param name="tf">tf (int): total time in units [s]</param>
    /// <param name="r0">r0 (ndarray): initial position array in units [RE]</param>
    /// <param name="v0">v0 (ndarray): initial velcoity array in units [m/s]</param>
    /// <param name="m">m (float): particle mass in units [kg]</param>
    /// <param name="q">q (float): particle charge in units [C]</param>
    /// <param name="gs">gs (float): shielding constant</param>
    /// <param name="kp">kp (float): kp index</param>
    /// <param name="tdir_fw">tdir (bool, optional): specifies forward tracing ['fw'] or backward tracing ['bw']. Defaults to 'fw.'</param>
    /// <param name="rmax">rmax (float, optional): maximum radial distance a particle is allowed to reach</param>
    /// <returns>Boris data structure containing return data.</returns>
    public static BorisReturns Boris(float tf, Vector3 r0, Vector3 v0, float m, float q, float gs, float kp, bool tdir_fw = true, float rmax = 10, float dn_save = 1, float dt_wci = 0.01f)
    {
        var RE = 6371000;

        // Calculate stepsize (dt) to be no bigger than half the gyroperiod
        var gyroperiod = (2 * PI) / ((Abs(q) * Mag(BDipole(r0 * RE))) / m);
        var dt = 0.01f * gyroperiod;
        var steps = (int)(tf / dt);
        var nout = (int)(steps / dn_save);

        Debug.Log("Run time: " + tf + ", Time step: " + dt + ", Steps: " + steps);

        var tdat = new float[nout];
        var rdat = new Vector3[nout];
        var vdat = new Vector3[nout];
        var emag = new float[nout];

        // Set initial conditions
        tdat[0] = 0;
        rdat[0] = r0;  // [RE]
        vdat[0] = v0;  // [RE/s]
        var isave = 1; // We have already saved the first data point at t=0
        var rnew = r0;
        var vnew = v0;

        // Forward vs. backward tracing
        var n = tdir_fw ? 1.0f : -1.0f;

        float tdrift = 0;

        for (int i = 0; i < steps; i++)
        {
            // Set current position and velocity (cartesian coords)
            var r = rnew; // rdat[i]
            var v = vnew; // vdat[i]

            // Compute B-field [T]
            var B0 = BDipole(r * RE, false);

            // Compute total E-field and covert to [V/m]
            var E0 = zero;

            // c0, ax, bx - arbitrary; to break down equation
            var c0 = (dt * q * B0) / (2 * m);

            // Push step 1 - update velocity with half electrostatic contribution
            var v1 = v + (n * (q * E0 * dt) / (2 * m));

            // Push step 2 - rotated via the magnetic field contribution
            var ax = v1 + (n * Cross(v1, c0));
            // var bx = (2 * c0) / (1 + (n * Pow(c0, 2))); POWER OF c0
            var bx = (2 * c0) / (1 + (n * Dot(c0, c0)));
            var v2 = v1 + (n * Cross(ax, bx));

            // Push step 3 - updated again with another half of the electrostatic push [m/s]
            vnew = v2 + (n * (q * E0 * dt) / (2 * m));

            // Update position [RE]
            rnew = r + (n * (vnew * dt) / RE);

            // Append to data arrays
            //   - Iteration i creates data for i+1
            if ((i + 1) % dn_save == 0)
            {
                tdat[isave] = (i + 1) * dt;     // if n == 1.0 else tf - i * dt  # time [s]
                vdat[isave] = vnew;             // Velcoity [m/s]
                rdat[isave] = rnew;             // Position [RE]
                emag[isave] = Mag(E0 / 1e-3f);  // Magnitude of total E-field [mV/m]
                isave += 1;
            }

            // Calculate driftt time when particle leaves L=10

            // Find positional magnitude
            var rmag = Sqrt(Dot(rnew, rnew));

            // Check if particle(s) crossed rmax
            if (rmag >= rmax)
            {
                tdrift = (i + 1) * dt;

                break;
            }
        }

        // Return struct
        BorisReturns returns = new BorisReturns();
        returns.tdat = tdat;
        returns.tdrift = tdrift;
        returns.vdat = vdat;
        returns.rdat = rdat;
        returns.emag = emag;
        return returns;
    }

    /// <summary>
    /// Data structure containing boris function returns.
    /// </summary>
    public struct BorisReturns
    {
        /// <summary>
        /// tdat (ndarray): time data in units [s]
        /// </summary>
        public float[] tdat;

        /// <summary>
        /// tdrift (ndarray): drift time in units [s]
        /// </summary>
        public float tdrift;

        /// <summary>
        /// vdat (ndarray): velocity data (spherical) in units [m/s]
        /// </summary>
        public Vector3[] vdat;

        /// <summary>
        /// rdat (ndarray): position data (spherical) in units [m]
        /// </summary>
        public Vector3[] rdat;

        /// <summary>
        /// emag (ndarray): magnitude of total E-field in units [mV/m]
        /// </summary>
        public float[] emag;
    }
}

/// <summary>
/// IMEF repository functions translated from Python to C#.
/// </summary>
public static class imef
{
    // bfields.py

    /// <summary>
    /// Compute Earth's dipole magnetic field at given cartesian coordinates.
    /// </summary>
    /// <param name="coords">coords (list): array of cartesian coordinates (x, y, z) in units [m]</param>
    /// <param name="sph">sph (bool, optional):  deterimes if input coordinates are in cartesian (False) or spherical (True); Defaults to False.</param>
    /// <returns>float: value of dipole field in units [T] or [kg*s^-2*A^-1]</returns>
    public static Vector3 B_dipole(Vector3 coords, bool sph = false)
    {
        Vector3 r;
        float phi;

        if (sph)
        {
            // Unpack coordinates
            var rdir = coords.x;
            var theta = coords.y;
            phi = coords.z;

            // Convert spherical to cartesian coordinates
            var x = rdir * Sin(theta) * Cos(phi);
            var y = rdir * Sin(theta) * Sin(phi);
            var z = rdir * Cos(theta);

            r = new Vector3(x, y, z);
        }
        else
        {
            r = coords;
        }

        // Tilt of magnetic axis [rad]
        phi = Deg2Rad * 11.7f;

        // Magnetic moment of earth [A*m^2]
        var mu = -7.94e22f * new Vector3(0, Sin(phi), Cos(phi));

        // mu_0 [N*A−2] /4*PI
        var M0 = 1.0e-7;

        var rmag = Sqrt(Dot(coords, coords));

        // Calculating dipole field
        var Bdip = (float)M0 * (3.0f * r * Dot(mu, r) / (Pow(rmag, 5)) - mu / (Pow(rmag, 3)));
        return Bdip;
    }


    // efields.py

    /// <summary>
    /// Calculate last closed equipotential (LCE).
    /// </summary>
    /// <returns>From Matsui et al.: In order to calculate such contours, we first search for maximum potential in the radial direction at a fixed MLT value, and then get the minimum of these maximum potentials in the whole MLT range.</returns>
    public static float get_LCE(float[] phidat, ref float[][] udat, float[][] pgrid, int dr)
    {
        // List to hold maximum potential at every MLT
        List<float> umax = new List<float>();

        // Find all coordinate locations at a fixed phi/MLT value, phi[N]
        for (int i = 0; i <= dr; i++)
        {
            var phi_loc = new Tuple<List<int>, List<int>>(new List<int>(), new List<int>());

            // Equivalent to np.where()
            for (int j = 0; j < pgrid.Length; j++)
            {
                if (phidat[j] == pgrid[i][j])
                {
                    phi_loc.Item1.Add(j);
                    phi_loc.Item2.Add(i);
                }
            }

            List<float> uvals = new List<float>();

            for (int j = 0; j <= dr; j++)
            {
                // Find locations where phi[N] exists
                var c1 = phi_loc.Item1[j];
                var c2 = phi_loc.Item2[j];

                // Find all potential values at phi[N]
                uvals.Add(udat[c1][c2]);
            }

            // Find maximum potential
            umax.Add(Max(uvals.ToArray()));
        }

        // Compute minimum of max potentials in the whole MLT range
        var LCE = Min(umax.ToArray());
        return LCE;
    }

    /// <summary>
    /// Compute corotation electric field in equatorial plane from given coordinates.
    /// </summary>
    /// <param name="coords">coords (ndarray): array of coordinates to compute efield in (x,y,z) or (r, theta, phi), with units in [m]; see 'sph' condition.</param>
    /// <param name="sph">sph (bool, optional): deterimes if input coordinates are in cartesian (False) or spherical (True); Defaults to False.</param>
    /// <returns>ndarray: coration E-field in 3 dimensions in units [mV/m]</returns>
    public static Vector3 corotation_efield(Vector3 coords, bool sph = false)
    {
        float rgeo;

        if (sph == false)
        {
            // Convert cartesian to spherical coordinates
            rgeo = crt_to_sph(coords[0], coords[1], coords[2]).x;
        }
        else
        {
            // Unpack coordinates
            rgeo = coords[0];
        }

        // Equatorial magnetic field strength at surface of Earth [T]
        var BE = 3.1e-5;

        // Engular velocity of the Earth’s rotation [rad/s]
        var omega = 7.2921e-5;

        // Equatorial radius of earth [m]
        var RE = 6371000;

        // Radial component with zero check
        var ER0 = (omega * BE * Pow(RE, 3)) / Pow(rgeo, 2);

        // Convert to [mV/m]
        ER0 *= 1000;

        // Return array [mV/m]
        var ER = -1 * new Vector3((float)ER0, 0, 0);
        return ER;
    }

    /// <summary>
    /// Compute corotation potential field in equatorial plane from given coordinates.
    /// </summary>
    /// <param name="coords">coords (ndarray): array of coordinates to compute efield in (x,y,z) or (r, theta, phi), with units in [m]; see 'sph' condition.</param>
    /// <param name="sph">sph (bool, optional): deterimes if input coordinates are in cartesian (False) or spherical (True); Defaults to False.</param>
    /// <returns>ndarray: magnitude of corotation potential in units [kV]</returns>
    public static double corotation_potential(Vector3 coords, bool sph = false)
    {
        float rgeo;

        if (sph == false)
        {
            // Convert cartesian to spherical coordinates
            rgeo = crt_to_sph(coords[0], coords[1], coords[2]).x;
        }
        else
        {
            // Unpack coordinates
            rgeo = coords[0];
        }

        // Equatorial magnetic field strength at surface of Earth [T]
        var BE = 3.1e-5;

        // Angular velocity of the Earth’s rotation [rad/s]
        var omega = 7.2921e-5;

        // Equatorial radius of earth [m]
        var RE = 6371000;

        // Calculate potential [V]
        var UR = (omega * Pow(RE, 3) * BE) / rgeo;

        // Return in units [kV]
        return UR * 1e-3;
    }

    /// <summary>
    /// Compute uniform convection electric field strength in equatorial plane in [kV/m^2] with given kp index. Based on Maynard and Chen 1975 (doi:10.1029/JA080i007p01009).
    /// </summary>
    /// <param name="kp">kp (float): kp index</param>
    /// <returns>float: A0; convection electric field strength in [mV/m^2]</returns>
    public static double convection_field_A0(float kp)
    {
        // Equatorial radius of earth [m]
        var RE = 6371000;

        // Uniform convection electric field strength in equatorial plane [kV/m^2]
        var A0 = 0.045 / ((1 - (0.159 * kp) + (Pow(0.0093f * (Pow(kp, 2)), 3))) * (Pow(RE, 2)));

        // Convert to [mV/m^2]
        A0 *= 1e6;

        return A0;
    }

    /// <summary>
    /// Compute Volland-Stern potential field. Model based on Volland 1973 (doi:10.1029/JA078i001p00171) and Stern 1975 (doi:10.1029/JA080i004p00595).
    /// </summary>
    /// <param name="coords">coords (ndarray): array of coordinates to compute efield in (x,y,z) or (r, theta, phi), with units in [m]; see 'sph' condition.</param>
    /// <param name="gs">gs (float): shielding constant</param>
    /// <param name="kp">kp (float): kp index</param>
    /// <param name="sph">sph (bool, optional): deterimes if input coordinates are in cartesian (False) or spherical (True); Defaults to False.</param>
    /// <returns>float: potential in units [kV]</returns>
    public static double vs_potential(Vector3 coords, float gs, float kp, bool sph = false)
    {
        float rgeo;
        float phi;

        if (sph == false)
        {
            // Convert cartesian to spherical coordinates
            var vec = crt_to_sph(coords[0], coords[1], coords[2]);
            rgeo = vec.x;
            phi = vec.z;
        }
        else
        {
            // Unpack coordinates
            rgeo = coords[0];
            phi = coords[2];
        }

        // Uniform convection electric field strength in equatorial plane [mV/m^2]
        var A0 = convection_field_A0(kp);

        // VS potential [mV]
        // 5/24/23 - might need to fix, add -92.4 component
        var U = -A0 * Pow(rgeo, gs) * Sin(phi);

        // Return potential in [kv]
        return -U * 1e-6;
    }

    /// <summary>
    /// Compute Volland-Stern conevction electric field.
    /// </summary>
    /// <param name="coords">coords (ndarray): array of coordinates to compute efield in (x,y,z) or (r, theta, phi), with units in [m]; see 'sph' condition.</param>
    /// <param name="gs">gs (float): shielding constant</param>
    /// <param name="kp">kp (float): kp index</param>
    /// <param name="sph">sph (bool, optional): deterimes if input coordinates are in cartesian (False) or spherical (True); Defaults to False.</param>
    /// <returns>ndarray: volland-stern field in 3 dimensions in units [mV/m].</returns>
    public static Vector3 vs_efield(Vector3 coords, float gs, float kp, bool sph = false)
    {
        float rgeo;
        float theta;
        float phi;

        if (sph == false)
        {
            // Convert cartesian to spherical coordinates
            var vec = crt_to_sph(coords[0], coords[1], coords[2]);
            rgeo = vec.x;
            theta = vec.y;
            phi = vec.z;
        }
        else
        {
            // Unpack coordinates
            rgeo = coords[0];
            theta = coords[1];
            phi = coords[2];
        }

        // Uniform convection electric field strength in equatorial plane [mV/m^2]
        var A0 = convection_field_A0(kp);

        // Radial componenet [mV/m]
        var EC0 = (-92.4 / Pow(rgeo, 2)) - (A0 * gs * (Pow(rgeo, (gs - 1))) * (Sin(phi)));

        // Polar component [mV/m]
        var EC1 = 0.0f;

        // Azimuthal component [mV/m]
        var EC2 = A0 * (Pow(rgeo, (gs - 1))) * (1 / (Sin(theta))) * (Cos(phi));

        // Return array [mV/m]
        var EC = new Vector3((float)EC0, EC1, (float)EC2);

        return EC;
    }


    // boris.py

    /// <summary>
    /// Compute magnitude of vector.
    /// </summary>
    /// <param name="vec"></param>
    /// <returns></returns>
    public static float mag(Vector3 vec)
    {
        var magnitude = Sqrt(Dot(vec, vec));
        return magnitude;
    }

    /// <summary>
    /// Convert cartesian to spherical coordinates/
    /// </summary>
    /// <param name="x">x -> r : radial distance</param>
    /// <param name="y">y -> theta : polar angle (radians)</param>
    /// <param name="z">z -> phi : azimuthal angle (radians)</param>
    /// <returns>(x, y, z) to (r, theta, phi)</returns>
    public static Vector3 crt_to_sph(float x, float y, float z)
    {
        var r = Sqrt(x * x + y * y + z * z);
        var theta = Acos(z / r);
        var phi = Atan2(y, x);

        return new Vector3(r, theta, phi);
    }

    /// <summary>
    /// Convert spherical to cartesian coordinates.
    /// </summary>
    /// <param name="r">r -> x : radial distance</param>
    /// <param name="theta">theta -> y : polar angle (radians)</param>
    /// <param name="phi">phi -> z : azimuthal angle (radians)</param>
    /// <returns>(r, theta, phi) to (x,y,z)</returns>
    public static Vector3 sph_to_crt(float r, float theta, float phi)
    {
        var x = r * Sin(theta) * Cos(phi);
        var y = r * Sin(theta) * Sin(phi);
        var z = r * Cos(theta);

        return new Vector3(x, y, z);
    }

    /// <summary>
    /// Boris particle pusher tracing code.
    /// </summary>
    /// <param name="tf">tf (int): total time in units [s]</param>
    /// <param name="r0">r0 (ndarray): initial position array in units [RE]</param>
    /// <param name="v0">v0 (ndarray): initial velcoity array in units [m/s]</param>
    /// <param name="m">m (float): particle mass in units [kg]</param>
    /// <param name="q">q (float): particle charge in units [C]</param>
    /// <param name="gs">gs (float): shielding constant</param>
    /// <param name="kp">kp (float): kp index</param>
    /// <param name="tdir_fw">tdir (bool, optional): specifies forward tracing ['fw'] or backward tracing ['bw']. Defaults to 'fw.'</param>
    /// <param name="rmax">rmax (float, optional): maximum radial distance a particle is allowed to reach</param>
    /// <returns>Boris data structure containing return data.</returns>
    public static boris_returns boris(float tf, Vector3 r0, Vector3 v0, float m, float q, float gs, float kp, bool tdir_fw = true, float rmax = 10, float dn_save = 1, float dt_wci = 0.01f)
    {
        var RE = 6371000;

        // Calculate stepsize (dt) to be no bigger than half the gyroperiod
        var gyroperiod = (2 * PI) / ((Abs(q) * mag(B_dipole(r0 * RE))) / m);
        var dt = 0.01f * gyroperiod;
        var steps = (int)(tf / dt);
        var nout = (int)(steps / dn_save);

        Debug.Log("Run time: " + tf + ", Time step: " + dt + ", Steps: " + steps);

        var tdat = new float[nout];
        var rdat = new Vector3[nout];
        var vdat = new Vector3[nout];
        var emag = new float[nout];

        // Set initial conditions
        tdat[0] = 0;
        rdat[0] = r0;  // [RE]
        vdat[0] = v0;  // [RE/s]
        var isave = 1; // We have already saved the first data point at t=0
        var rnew = r0;
        var vnew = v0;

        // Forward vs. backward tracing
        var n = tdir_fw ? 1.0f : -1.0f;

        float tdrift = 0;

        for (int i = 0; i < steps; i++)
        {
            // Set current position and velocity (cartesian coords)
            var r = rnew; // rdat[i]
            var v = vnew; // vdat[i]

            // Compute B-field [T]
            var B0 = B_dipole(r * RE, false);

            // Compute total E-field and covert to [V/m]
            var E0 = zero;

            // c0, ax, bx - arbitrary; to break down equation
            var c0 = (dt * q * B0) / (2 * m);

            // Push step 1 - update velocity with half electrostatic contribution
            var v1 = v + (n * (q * E0 * dt) / (2 * m));

            // Push step 2 - rotated via the magnetic field contribution
            var ax = v1 + (n * Cross(v1, c0));
            // var bx = (2 * c0) / (1 + (n * Pow(c0, 2))); POWER OF c0
            var bx = (2 * c0) / (1 + (n * Dot(c0, c0)));
            var v2 = v1 + (n * Cross(ax, bx));

            // Push step 3 - updated again with another half of the electrostatic push [m/s]
            vnew = v2 + (n * (q * E0 * dt) / (2 * m));

            // Update position [RE]
            rnew = r + (n * (vnew * dt) / RE);

            // Append to data arrays
            //   - Iteration i creates data for i+1
            if ((i + 1) % dn_save == 0)
            {
                tdat[isave] = (i + 1) * dt;     // if n == 1.0 else tf - i * dt  # time [s]
                vdat[isave] = vnew;             // Velcoity [m/s]
                rdat[isave] = rnew;             // Position [RE]
                emag[isave] = mag(E0 / 1e-3f);  // Magnitude of total E-field [mV/m]
                isave += 1;
            }

            // Calculate driftt time when particle leaves L=10

            // Find positional magnitude
            var rmag = Sqrt(Dot(rnew, rnew));

            // Check if particle(s) crossed rmax
            if (rmag >= rmax)
            {
                tdrift = (i + 1) * dt;

                break;
            }
        }

        // Return struct
        boris_returns returns = new boris_returns();
        returns.tdat = tdat;
        returns.tdrift = tdrift;
        returns.vdat = vdat;
        returns.rdat = rdat;
        returns.emag = emag;
        return returns;
    }

    /// <summary>
    /// Data structure containing boris function returns.
    /// </summary>
    public struct boris_returns
    {
        /// <summary>
        /// tdat (ndarray): time data in units [s]
        /// </summary>
        public float[] tdat;

        /// <summary>
        /// tdrift (ndarray): drift time in units [s]
        /// </summary>
        public float tdrift;

        /// <summary>
        /// vdat (ndarray): velocity data (spherical) in units [m/s]
        /// </summary>
        public Vector3[] vdat;

        /// <summary>
        /// rdat (ndarray): position data (spherical) in units [m]
        /// </summary>
        public Vector3[] rdat;

        /// <summary>
        /// emag (ndarray): magnitude of total E-field in units [mV/m]
        /// </summary>
        public float[] emag;
    }
}
