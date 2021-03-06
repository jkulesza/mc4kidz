#pragma once
#include <cassert>
#include <cmath>
#include <cstdint>
#include <random>
#include <vector>

#include "materials.h"
#include "mesh.h"
#include "particle.h"
#include "shapes.h"

enum class BoundaryCondition : uint8_t { VACUUM, REFLECTIVE };

class State {
public:
    State();

    // Wipe out any existing particles and spawn a new batch
    void reset();

    // Simulate the motion of particles for a frame/time step.
    // Handle collisions that occur
    void tic();

    void draw() const;

    // Switch to the next boundary condition type
    void toggle_boundary_condition();

    void toggle_waypoints()
    {
        _draw_waypoints = !_draw_waypoints;
    }

    // Sample a particle interaction. Return whether the particle survived.
    void interact(size_t id);

private:
    const Color PARTICLE_COLOR{1.0f, 1.0f, 0.0f, 1.0f};
    const Color PARTICLE_DEST_COLOR{0.0f, 0.0f, 1.0f, 1.0f};
    const Color PIN_COLOR{0.5f, 0.0f, 0.0f, 1.0f};
    const int NPINS_X      = 10;
    const int NPINS_Y      = 10;
    const float PIN_RADIUS = 0.4f;
    const float PIN_PITCH  = 1.0f;

    std::vector<Particle> _particles;
    // Collection of indices into _particles which need to process a collision this time
    // step.
    // Kept as object state to prevent reallocation.
    std::vector<size_t> _process_queue;
    MaterialLibrary _materials;
    Mesh _mesh;
    Box _boundary;
    BoundaryCondition _bc = BoundaryCondition::VACUUM;
    std::default_random_engine _random;
    std::uniform_real_distribution<float> _angle_distribution;
    std::uniform_real_distribution<float> _unit_distribution;
    bool _draw_waypoints = false;
};
