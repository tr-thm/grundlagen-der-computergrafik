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

#include "simulation.h"

#include <chrono>

Simulation::Simulation(const std::shared_ptr<Mesh> &earth, const std::shared_ptr<Mesh> &satellite)
{
    this->earth = earth;
    this->satellite = satellite;
}

void Simulation::update()
{
    auto time = std::chrono::system_clock::now();
    auto timeSinceEpoch = time.time_since_epoch();
    double secondsSinceEpoch = std::chrono::duration<double>(timeSinceEpoch).count();

    updateEarthRotation(secondsSinceEpoch);
    updateSatellitePosition(secondsSinceEpoch);
}

void Simulation::updateEarthRotation(double time)
{
    double timeOfDay = std::fmod(time, 86400);
    double earthRotation = timeOfDay / 86400.0 * deg2rad(360);

    int timeOfYear = std::fmod(time + 864000.0, 31557600);

    double earthEcliptic = cos(timeOfYear / 31557600.0 * deg2rad(360)) * deg2rad(-23.4);

    earth->setRotation(Vector3(earthEcliptic, earthRotation, 0));
}

void Simulation::updateSatellitePosition(double time)
{
    double scale = 25.0 / 6370.0;

    double orbitTime = 5400.0;
    double orbitProgress = std::fmod(time, orbitTime);

    double orbitRadius = 6770.0 / 6370.0;
    Vector4 position = Vector4(0.0, 0.0, orbitRadius, 1.0);

    Matrix4 orbit = Matrix4::rotateX(deg2rad(45)) * Matrix4::rotateY(orbitProgress / orbitTime * deg2rad(360.0));
    position = orbit * position;

    double tumbleTime = 60.0;
    double tumbleProgress = std::fmod(time, tumbleTime);
    double tumble = tumbleProgress / tumbleTime * deg2rad(360.0);
    
    satellite->setScale(scale);
    satellite->setPosition(position.xyz());
    satellite->setRotation(Vector3(tumble, tumble, tumble));
}