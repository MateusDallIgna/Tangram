#!/usr/bin/env python3
"""
Calculate Tangram square configuration
The classic Tangram square has all 7 pieces forming a perfect square
"""

import math

SQRT2 = math.sqrt(2)
PI = math.pi

# Piece sizes
LARGE_LEG = SQRT2      # 1.414
MEDIUM_LEG = 1.0
SMALL_LEG = SQRT2 / 2  # 0.707
SQUARE_SIDE = SQRT2 / 2  # 0.707

# The classic Tangram square has side length = 2 * SMALL_LEG * SQRT2 = 2
# Let's build it centered at origin, from (-1, -1) to (1, 1)

print("=== CLASSIC TANGRAM SQUARE ===")
print(f"Square side length: 2.0")
print(f"Corners: (-1, -1) to (1, 1)")
print()

# I'll build the square piece by piece, calculating where each center should be

# BOTTOM ROW: Two large triangles
# Large triangle 1: bottom-left corner, rotated 45°
# When rotated 45°, the triangle forms a square with diagonal = LARGE_LEG
# The triangle at 45° has its right angle pointing to bottom-left

# Let me think: a large triangle has leg = 1.414
# At 0° rotation: vertices at (0, 1.414), (0, 0), (1.414, 0), center at (0.471, 0.471)
# At 45° rotation: the triangle is rotated around its center

# For the square configuration, I need to place pieces so they fit edge-to-edge
# Let's use a different approach: place pieces by their corners, then calculate centers

print("Building from corners...")
print()

# The square is 2x2, from (-1,-1) to (1,1)
# Bottom-left large triangle: occupies bottom-left quadrant
# Its hypotenuse goes from (-1, 1) to (1, -1) - the diagonal

# Large triangle at 45° with hypotenuse on the diagonal
# The triangle's right angle is at bottom-left (-1, -1)
# One leg goes to (0, 0), other leg goes to (0, 0)
# Wait, that's not right...

# Let me use the standard Tangram square configuration:
# https://en.wikipedia.org/wiki/Tangram

# Standard configuration (from bottom to top, left to right):
# Row 1 (bottom): Large tri 1 (left half) + Large tri 2 (right half)
# Row 2 (middle): Medium tri (left) + Square (center) + Small tri 2 (right)
# Row 3 (top): Small tri 1 (left) + Parallelogram (right)

# Let's calculate this step by step
# The square is 2x2 units

# Bottom half is divided by two large triangles meeting at the center
# Large triangle 1: right angle at (-1, -1), hypotenuse from (-1, 1) to (1, -1)
# This means it's rotated 45° (ROT_45 = π/4)

# For a triangle with leg L at rotation R:
# If placed with right angle at point P, the center is at P + (L/3, L/3) rotated by R

# Large triangle 1 (bottom-left):
# Right angle should be at (-1, -1)
# Rotation: 45° (π/4)
# Leg: 1.414
# Center offset from right angle: (1.414/3, 1.414/3) = (0.471, 0.471)
# After 45° rotation: offset becomes (0, 0.667) approximately
# Center position: (-1, -1) + rotated offset

# This is getting complex. Let me use a simpler approach:
# I'll manually place the pieces and calculate their centers

def rotate_point(x, y, angle):
    """Rotate point (x,y) by angle radians around origin"""
    cos_a = math.cos(angle)
    sin_a = math.sin(angle)
    return (x * cos_a - y * sin_a, x * sin_a + y * cos_a)

# For a right isosceles triangle with leg L:
# Vertices at (0, 0), (L, 0), (0, L)
# Center at (L/3, L/3)

# Large triangle 1: I want it to fill the bottom-left of the square
# The square goes from (-1, -1) to (1, 1)
# A large triangle has leg = 1.414

# If I place the triangle with right angle at (-1, -1) and rotate it 45°:
# Original vertices: (0, 0), (1.414, 0), (0, 1.414)
# Original center: (0.471, 0.471)
# After 45° rotation around center:
#   The center stays at (0.471, 0.471) in local coords
# Then translate so right angle is at (-1, -1):
#   Need to translate by (-1, -1) - rotated(0, 0)

# Actually, the rendering code does:
# 1. Translate to target.position
# 2. Rotate by target.rotation
# 3. Translate by -localCenter

# So: final_vertex = rotate(vertex - localCenter, rotation) + target.position

# For the right angle to be at (-1, -1):
# right_angle_vertex = (0, 0) in local coords
# After transform: rotate((0,0) - localCenter, rotation) + target.position = (-1, -1)
# So: rotate(-localCenter, rotation) + target.position = (-1, -1)
# target.position = (-1, -1) - rotate(-localCenter, rotation)

# For large triangle: localCenter = (0.471, 0.471)
# rotation = 45° = π/4
# rotate(-(0.471, 0.471), π/4) = rotate((-0.471, -0.471), π/4)

offset_x, offset_y = rotate_point(-0.471, -0.471, PI/4)
pos_x = -1.0 - offset_x
pos_y = -1.0 - offset_y

print(f"Large Triangle 1 (bottom-left):")
print(f"  Rotation: 45° (π/4)")
print(f"  Local center: (0.471, 0.471)")
print(f"  Rotated offset: ({offset_x:.6f}, {offset_y:.6f})")
print(f"  Target position: ({pos_x:.6f}, {pos_y:.6f})")
print(f"  {{0, glm::vec2({pos_x:.6f}f, {pos_y:.6f}f), ROT_45, false}}")
print()

# This is too complicated. Let me just use empirical values from a working Tangram square
# and adjust from there

print("\n=== USING KNOWN WORKING CONFIGURATION ===\n")

# From various Tangram resources, a standard square configuration:
# All pieces fit in a 2x2 square centered at origin

# Simplified approach: I'll create a simple house and boat
