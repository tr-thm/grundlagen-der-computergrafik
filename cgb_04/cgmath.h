/**
 * Grundlagen der Computergrafik
 * Copyright © 2021-2024 Tobias Reimann
 * Copyright © 2024 Lukas Scheurer: Rewritten in C++
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <cmath>
#include <numbers>

inline double deg2rad(double deg)
{
    return deg * std::numbers::pi / 180.0;
}

struct Matrix4
{
    double m11;  double m21;  double m31;  double m41;
    double m12;  double m22;  double m32;  double m42;
    double m13;  double m23;  double m33;  double m43;
    double m14;  double m24;  double m34;  double m44;

    /**
     * Creates a translation matrix that translates points
     * by the given x, y, and z values.
     *
     * @param x The translation distance along the x-axis.
     * @param y The translation distance along the y-axis.
     * @param z The translation distance along the z-axis.
     * @return The translation matrix.
     */
    static Matrix4 translate(double x, double y, double z)
    {
        Matrix4 m = {
            1, 0, 0, x,
            0, 1, 0, y,
            0, 0, 1, z,
            0, 0, 0, 1
        };
        return m;
    }

    /**
     * Creates a rotation matrix for a rotation around the X-axis.
     * 
     * @param a The angle of rotation in radians.
     * @return The rotation matrix.
     */
    static Matrix4 rotateX(double a)
    {
        Matrix4 m = {
            1,      0,       0, 0,
            0, cos(a), -sin(a), 0,
            0, sin(a),  cos(a), 0,
            0,      0,       0, 1
        };
        return m;
    }

    /**
     * Creates a rotation matrix for a rotation around the Y-axis.
     * 
     * @param a The angle of rotation in radians.
     * @return The rotation matrix.
     */
    static Matrix4 rotateY(double a)
    {
        Matrix4 m = {
             cos(a), 0, sin(a), 0,
                  0, 1,      0, 0,
            -sin(a), 0, cos(a), 0,
                  0, 0,      0, 1
        };
        return m;
    }

    /**
     * Creates a rotation matrix for a rotation around the Z-axis.
     * 
     * @param a The angle of rotation in radians.
     * @return The rotation matrix.
     */
    static Matrix4 rotateZ(double a)
    {
        Matrix4 m = {
            cos(a), -sin(a), 0, 0,
            sin(a),  cos(a), 0, 0,
                 0,       0, 1, 0,
                 0,       0, 0, 1
        };
        return m;
    }

    /**
     * Converts the matrix to column-major order and stores the result in the provided array.
     * 
     * @param values A reference to a 16-element array of floats where the column-major matrix elements will be stored.
     */
    void toColumnMajor(float (&values)[16]) const
    {
        values[0] = static_cast<float>(m11);
        values[1] = static_cast<float>(m12);
        values[2] = static_cast<float>(m13);
        values[3] = static_cast<float>(m14);
        values[4] = static_cast<float>(m21);
        values[5] = static_cast<float>(m22);
        values[6] = static_cast<float>(m23);
        values[7] = static_cast<float>(m24);
        values[8] = static_cast<float>(m31);
        values[9] = static_cast<float>(m32);
        values[10] = static_cast<float>(m33);
        values[11] = static_cast<float>(m34);
        values[12] = static_cast<float>(m41);
        values[13] = static_cast<float>(m42);
        values[14] = static_cast<float>(m43);
        values[15] = static_cast<float>(m44);
    }
};