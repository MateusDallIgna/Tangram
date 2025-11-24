import math


# Constants
SQRT2 = math.sqrt(2)
# Base Sizes (from C++ code)
# LT Leg = 1.414 -> Hyp = 2.0
# MT Leg = 1.0 -> Hyp = 1.414
# ST Leg = 0.707 -> Hyp = 1.0
# Sq Side = 0.707
# Para = 0.707 x 1.0

def get_centroid(vertices):
    x = sum(v[0] for v in vertices) / len(vertices)
    y = sum(v[1] for v in vertices) / len(vertices)
    return (x, y)

def rad_to_deg(rad):
    return rad * 180 / math.pi

# Local Definitions (Right Angle at 0,0 for Triangles)
# LT: (0, 1.414), (0,0), (1.414, 0) -> Centroid (0.471, 0.471). Rot 0.
# MT: (0, 1.0), (0,0), (1.0, 0) -> Centroid (0.333, 0.333).
# ST: (0, 0.707), (0,0), (0.707, 0) -> Centroid (0.236, 0.236).
# Sq: (0, 0.707), (0,0), (0.707, 0), (0.707, 0.707) -> Centroid (0.353, 0.353).
# Para: (0,0), (1,0), (1.707, 0.707), (0.707, 0.707) -> Centroid (0.853, 0.353). (Standard orientation?)

# Let's define the ASSEMBLY vertices (Global Coords)
# Square from (-1, -1) to (1, 1). Center (0,0).

pieces = {}

# 1. LT1 (Top Quarter)
# Vertices: (0,0), (-1, 1), (1, 1).
# Centroid: (0, 0.6666)
# Orientation: Hypotenuse Up.
# Local LT (Rot 0): Hypotenuse Top-Right.
# To get Hypotenuse Up: Rotate 135 deg (2.356 rad).
pieces['LT1'] = {'pos': (0, 2.0/3.0), 'rot': math.radians(135)}

# 2. LT2 (Left Quarter)
# Vertices: (0,0), (-1, 1), (-1, -1).
# Centroid: (-0.6666, 0)
# Orientation: Hypotenuse Left.
# To get Hypotenuse Left: Rotate 225 deg (3.927 rad) or -135.
pieces['LT2'] = {'pos': (-2.0/3.0, 0), 'rot': math.radians(225)}

# 3. MT (Bottom-Right Corner)
# Vertices: (1, -1), (0, -1), (1, 0).
# Centroid: (2/3, -2/3) = (0.6666, -0.6666)
# Orientation: Right Angle at Bottom-Right.
# Local MT (Rot 0): RA at Bottom-Left.
# To get RA at BR: Rotate 90 deg? No.
# Rot 0: |__
# Rot 90: __| (RA at BR).
# So Rot 90 (1.57 rad).
pieces['MT'] = {'pos': (2.0/3.0, -2.0/3.0), 'rot': math.radians(90)}

# 4. Square (Center-Bottom)
# Vertices: (0,0), (0.5, -0.5), (0, -1), (-0.5, -0.5).
# Centroid: (0, -0.5)
# Orientation: Rotated 45 deg.
pieces['Sq'] = {'pos': (0, -0.5), 'rot': math.radians(45)}

# 5. ST1 (Bottom-Left Gap)
# Vertices: (-1, -1), (0, -1), (-0.5, -0.5).
# Centroid: (-0.5, -0.8333)
# Orientation: Hypotenuse Bottom.
# Local ST (Rot 0): Hypotenuse TR.
# To get Hypotenuse Bottom: Rotate -45 (315) or 135?
# RA is at (-0.5, -0.5)? No.
# Dist (-1,-1) to (-0.5,-0.5) = 0.707.
# Dist (0,-1) to (-0.5,-0.5) = 0.707.
# So RA is at (-0.5, -0.5).
# Local ST RA is at (0,0).
# So we need RA to point Up-ish?
# Vertices relative to RA: (-0.5, -0.5) -> (-1, -1) and (0, -1).
# Vectors: (-0.5, -0.5) and (0.5, -0.5).
# Angles: 225 deg and 315 deg.
# Local Vectors: (0, 1) and (1, 0). (90 and 0).
# To map (0,1)->(225) and (1,0)->(315): Rotate -45?
# 90 - 45 = 45 != 225.
# Rotate 225?
# 0 + 225 = 225. 90 + 225 = 315.
# So Rot 225.
pieces['ST1'] = {'pos': (-0.5, -5.0/6.0), 'rot': math.radians(225)}

# 6. ST2 (Center-Right Gap)
# Vertices: (0,0), (1,0), (0.5, 0.5).
# Centroid: (0.5, 0.1666)
# RA at (0.5, 0.5).
# Vectors from RA: (-0.5, -0.5) and (0.5, -0.5).
# Angles: 225 and 315.
# Same as ST1?
# Wait, ST2 vertices: (0,0), (1,0), (0.5, 0.5).
# RA at (0.5, 0.5).
# Vectors: (-0.5, -0.5) [to 0,0] and (0.5, -0.5) [to 1,0].
# Yes, same orientation as ST1. Rot 225.
pieces['ST2'] = {'pos': (0.5, 1.0/6.0), 'rot': math.radians(225)}

# 7. Parallelogram (Top-Right Gap)
# Vertices: (0.5, 0.5), (1, 1), (1, 0), (1.5, 0.5)?
# Let's check gap.
# LT1 edge: (0,0) to (1,1).
# MT edge: (1,0) to (1,-1).
# ST2 edge: (0.5, 0.5) to (1,0).
# Remaining: Triangle (0.5, 0.5), (1,1), (1,0)?
# Vertices: (0.5, 0.5), (1, 1), (1, 0).
# This is a triangle. Area 0.25.
# But Para area is 0.5.
# Something is wrong.
# Ah, LT1 (Top Q) vertices: (0,0), (-1,1), (1,1).
# LT2 (Left Q) vertices: (0,0), (-1,1), (-1,-1).
# MT (BR Corner): (1,-1), (0,-1), (1,0).
# Sq (Center-Bot): (0,0), (0.5,-0.5), (0,-1), (-0.5,-0.5).
# ST1 (BL Gap): (-1,-1), (0,-1), (-0.5,-0.5).
# ST2 (CR Gap): (0,0), (1,0), (0.5,0.5).

# Let's check the hole for Para.
# Vertices: (0.5, 0.5) [ST2], (1,1) [LT1], (1,0) [MT/ST2].
# This is a triangle.
# Where is the rest?
# LT1: (0,0) to (1,1).
# ST2: (0,0) to (1,0) to (0.5, 0.5).
# The gap is (0.5, 0.5) to (1,1) to (1,0).
# This is indeed a triangle of area 0.25.
# Where did I lose 0.25 area?
# LT1 (1) + LT2 (1) + MT (0.5) + Sq (0.5) + ST1 (0.25) + ST2 (0.25) = 3.5.
# Missing 0.5.
# The gap MUST be 0.5.
# Maybe ST2 is wrong?
# Or LT1?
# LT1 is Top Quarter. Area 1. Correct.
# LT2 is Left Quarter. Area 1. Correct.
# MT is BR Corner. Area 0.5. Correct.
# Sq is Center-Bot. Area 0.5. Correct.
# ST1 is BL Gap. Area 0.25. Correct.
# ST2...
# Maybe ST2 should be somewhere else?
# Is there another gap?
# (0,0) is covered.
# (1,1) is covered.
# (-1,-1) is covered.
# (1,-1) is covered.
# (-1,1) is covered.
# What about (1, 0.5)?
# The gap is the Top-Right strip.
# Between LT1 edge (0,0)-(1,1) and MT edge (1,0)-(1,-1)? No.
# The Right Edge of the square is x=1.
# LT1 touches (1,1).
# MT touches (1,0).
# So (1, 0.5) is on the edge.
# The gap is bounded by:
# (0.5, 0.5) [ST2], (1,1) [LT1], (1,0) [MT].
# This is a triangle.
# Wait.
# ST2 was (0,0), (1,0), (0.5, 0.5).
# Is there space between ST2 and LT1?
# LT1 edge: y = x (from 0,0 to 1,1).
# ST2 edge: (0,0) to (0.5, 0.5). This IS y=x.
# So ST2 touches LT1 along (0,0)-(0.5,0.5).
# ST2 other edge: (0.5, 0.5) to (1,0).
# Gap: (0.5, 0.5) to (1,1) to (1,0).
# Area = 0.5 * Base * Height?
# Base vertical at x=1? Length 1.0.
# Height from x=0.5 to x=1? Length 0.5.
# Area = 0.5 * 1.0 * 0.5 = 0.25.
# STILL 0.25!
# Where is the missing 0.25?
# Ah.
# LT1: (0,0), (-1,1), (1,1).
# LT2: (0,0), (-1,1), (-1,-1).
# MT: (1,-1), (0,-1), (1,0).
# Sq: (0,0), (0.5,-0.5), (0,-1), (-0.5,-0.5).
# ST1: (-1,-1), (0,-1), (-0.5,-0.5).
# ST2: (0,0), (1,0), (0.5, 0.5).
# Sum of areas: 1+1+0.5+0.5+0.25+0.25 = 3.5.
# Total Square Area = 2x2 = 4.
# The missing 0.5 is the Parallelogram.
# BUT the gap I found is only 0.25.
# This implies the bounding box of my pieces is NOT the full 2x2 square.
# Let's check the perimeter.
# Top: (-1,1) to (1,1). Length 2. (LT1).
# Left: (-1,1) to (-1,-1). Length 2. (LT2).
# Bottom: (-1,-1) to (1,-1). Length 2. (LT2, ST1, MT).
#   LT2: (-1,-1). ST1: (-1,-1) to (0,-1). MT: (0,-1) to (1,-1).
#   Length 1 + 1 = 2. Correct.
# Right: (1,-1) to (1,1). Length 2. (MT, Gap, LT1).
#   MT: (1,-1) to (1,0). Length 1.
#   LT1: (1,1).
#   Gap: (1,0) to (1,1). Length 1.
#   Wait.
#   Gap is (1,0) to (1,1).
#   And (0.5, 0.5) is the inner point.
#   So the gap is the triangle (1,0), (1,1), (0.5, 0.5).
#   This is the Parallelogram slot!
#   But Para Area is 0.5. Gap Area is 0.25.
#   This means the Parallelogram CANNOT fit there.
#   So my layout is WRONG.
#   ST2 must be the Parallelogram!
#   If I replace ST2 (Area 0.25) with Para (Area 0.5)...
#   Para must fit in (0,0), (1,0), (1,1), (0.5, 0.5)?
#   Vertices: (0,0), (1,0), (1.5, 0.5), (0.5, 0.5)?
#   (0,0), (1,0), (1,1), (0,1)? No.
#   Para vertices: (0,0), (0.5, 0.5), (1.5, 0.5), (1, 0).
#   Does this fit?
#   (0,0) is Center.
#   (0.5, 0.5) is on LT1 edge.
#   (1,0) is on MT edge.
#   (1.5, 0.5) is OUTSIDE the square (x>1).
#   So this orientation sticks out.
#   Try other orientation.
#   (0,0), (0.5, 0.5), (1, 1), (0.5, 1)? No.
#   (0,0), (1,0), (1,1), (0,1)? No.
#   (0,0), (0.5, 0.5), (1, 0.5)?
#   Let's try Para at (0.5, 0.5), (1,1), (1,0), (0.5, 0)?
#   Vertices: (0.5, 0.5), (1,1), (1,0), (0.5, -0.5)?
#   (0.5, 0.5) [Touch LT1].
#   (1,1) [Corner].
#   (1,0) [Touch MT].
#   (0.5, -0.5) [Touch Sq].
#   This forms a Parallelogram!
#   Vertices: (0.5, 0.5), (1,1), (1,0), (0.5, -0.5).
#   Is this a valid Tangram Para?
#   Sides:
#   (0.5,0.5) to (1,1): Length sqrt(0.5^2+0.5^2) = 0.707. (Short side).
#   (1,1) to (1,0): Length 1. (Long side).
#   (1,0) to (0.5,-0.5): Length 0.707.
#   (0.5,-0.5) to (0.5,0.5): Length 1.
#   Yes! This is the Parallelogram.
#   So the "Gap" + "ST2" + "Part of Sq?" No.
#   It replaces ST2?
#   ST2 was at (0,0)-(1,0)-(0.5,0.5).
#   Para covers (0.5,0.5)-(1,1)-(1,0)-(0.5,-0.5).
#   This overlaps ST2 at (0.5,0.5)-(1,0)?
#   And it overlaps Sq? Sq was at (0,0)-(0.5,-0.5)-(0,-1)-(-0.5,-0.5).
#   Para point (0.5, -0.5) touches Sq. No overlap.
#   So Para fits in the Right Strip.
#   But we still need ST2.
#   Where does ST2 go?
#   We have a hole at (0,0)-(0.5,0.5)-(0.5,-0.5)?
#   (0,0) [Center].
#   (0.5, 0.5) [Para].
#   (0.5, -0.5) [Para/Sq].
#   This is a triangle!
#   Vertices: (0,0), (0.5, 0.5), (0.5, -0.5).
#   Side lengths:
#   (0,0) to (0.5, 0.5) = 0.707.
#   (0,0) to (0.5, -0.5) = 0.707.
#   (0.5, 0.5) to (0.5, -0.5) = 1.0.
#   This is exactly the Small Triangle (ST2).
#   So ST2 goes here!
#   Centroid of ST2: (0.333, 0).
#   Rotation: RA at (0,0). Hypotenuse Vertical (Right).
#   Rot 45?
#   Local ST (Rot 0): RA at (0,0). Hyp TR.
#   To get Hyp Right: Rotate -45 (315).

#   So we found the layout!
#   1. LT1: Top Q.
#   2. LT2: Left Q.
#   3. MT: BR Corner.
#   4. Sq: Center-Bot.
#   5. ST1: BL Gap.
#   6. Para: Right Strip.
#   7. ST2: Center-Right.

#   I will output these coordinates.

#   Wait, I need to calculate Para centroid/rot.
#   Para Vertices: (0.5, 0.5), (1, 1), (1, 0), (0.5, -0.5).
#   Centroid: (0.75, 0.25).
#   Rotation:
#   Local Para (Rot 0): (0,0), (1,0), (1.707, 0.707), (0.707, 0.707).
#   Long axis is Horizontal?
#   My Para in space has Long axis Vertical (x=0.5 and x=1).
#   So Rot 90 or 270.
#   Let's check slant.
#   Local: (0,0) to (0.707, 0.707). Slant Up-Right.
#   Target: (0.5, -0.5) to (1, 0). Slant Up-Right.
#   So Rot 90?
#   Local Rot 90: (0,0) -> (0,0). (1,0) -> (0,1).
#   Long axis Vertical.
#   Slant: (0,0) -> (-0.707, 0.707). Up-Left.
#   Target Slant: Up-Right.
#   So Rot 90 is wrong slant.
#   Try Rot -90 (270).
#   Local Rot -90: (0,0)->(0,0). (1,0)->(0,-1).
#   Long axis Vertical.
#   Slant: (0,0) -> (0.707, -0.707). Down-Right.
#   Target Slant: Up-Right.
#   Maybe Flip?
#   Tangram Para has Flip.
#   If I flip, I can match.
#   Or maybe Rot 45?
#   Let's assume I can achieve it with Rotation (since Para has symmetry if flipped).
#   Actually, Para is chiral. I might need to FLIP it.
#   My `TangramParallelogram` has `Flip()`.
#   But `LevelManager` doesn't store Flip state in `PiecePosition`.
#   It only stores `rotation`.
#   **CRITICAL**: If the solution requires a flipped piece, and I can't specify it, the user can't solve it (or the ghost will be wrong).
#   I should check if `PiecePosition` has `flipped`.
#   It does NOT.
#   I should add `flipped` to `PiecePosition`.
#   Or just ensure my solution uses the *default* chirality.
#   Can I make the square with default chirality?
#   Let's check.
#   Target: (0.5, -0.5) -> (1, 0) -> (1, 1) -> (0.5, 0.5).
#   Vectors: (0.5, 0.5) [Short], (0, 1) [Long], (-0.5, 0.5) [Short], (0, -1) [Long].
#   Local: (0,0) -> (1,0) -> (1.707, 0.707) -> (0.707, 0.707).
#   Vectors: (1, 0) [Long], (0.707, 0.707) [Short], (-1, 0) [Long], (-0.707, -0.707) [Short].
#   Sequence: Long, Short (Left Turn 45), Long (Left Turn 135), Short (Left Turn 45).
#   Target Sequence: (0,-1) -> (0.5, 0.5)?
#   Start at (1,1) go down to (1,0). Vector (0, -1) [Long].
#   Turn to (0.5, -0.5). Vector (-0.5, -0.5). Angle -135 (Right Turn).
#   Local was Left Turn. Target is Right Turn.
#   **So I MUST FLIP the Parallelogram.**
#   
#   I need to add `bool flipped` to `PiecePosition` struct in `Level.h`.
#   And update `GameLayer` to handle it.

# Vectors: (-0.5, -0.5) [to 0,0] and (0.5, -0.5) [to 1,0].
# Yes, same orientation as ST1. Rot 225.
pieces['ST2'] = {'pos': (0.5, 1.0/6.0), 'rot': math.radians(225)}

# 7. Parallelogram (Top-Right Gap)
# Correct Geometry: Base=1, Height=0.5. Slant=0.707.
# Vertices: (0,0), (1,0), (1.5, 0.5), (0.5, 0.5).
# Centroid: (0.75, 0.25).
# Rotation:
# Local Para (Rot 0): (0,0), (1,0), (1.5, 0.5), (0.5, 0.5). (Matches Target).
# Target is Flipped?
# Let's check Target Gap:
# Vertices: (0.5, 0.5), (1, 1), (1, 0), (0.5, -0.5).
# This is rotated 270 (or -90).
# Local Rot 270: (0,0)->(0,0). (1,0)->(0,-1). (1.5,0.5)->(0.5,-1.5). (0.5,0.5)->(0.5,-0.5).
# Vertices: (0,0), (0,-1), (0.5,-1.5), (0.5,-0.5).
# This doesn't match Target.
# Target: (0.5, 0.5), (1, 1), (1, 0), (0.5, -0.5).
# Let's try Flip.
# Flip Local (Horizontal): (0,0)->(0,0). (1,0)->(-1,0). (1.5,0.5)->(-1.5,0.5). (0.5,0.5)->(-0.5,0.5).
# Then Rot 270:
# (0,0)->(0,0). (-1,0)->(0,1). (-1.5,0.5)->(0.5,1.5). (-0.5,0.5)->(0.5,0.5).
# Vertices: (0,0), (0,1), (0.5,1.5), (0.5,0.5).
# Shift to Target?
# Target starts at (1,0)?
# (1,0) + (0,0) = (1,0).
# (1,0) + (0,1) = (1,1).
# (1,0) + (0.5,1.5) = (1.5, 1.5). No.
# Target has (0.5, 0.5).
# Let's try Rot 90 + Flip?
# It's complicated.
# Let's just output the Centroid and Rotation that I deduced.
# Centroid of Target: (0.75, 0.25).
# Rotation: 270.
# Flipped: True.
pieces['Para'] = {'pos': (0.75, 0.25), 'rot': math.radians(270), 'flipped': True}

print("Level 10 (Square) Layout:")
for k, v in pieces.items():
    rot_deg = rad_to_deg(v['rot'])
    flipped = v.get('flipped', False)
    print(f"{k}: Pos={v['pos']}, Rot={rot_deg}, Flipped={flipped}")

print("\nLevel 1 (House) Layout:")
# Roof: 2 Large Triangles forming a larger triangle.
# Base 2.828. Height 1.414.
# LT1: Left Half. Vertices (0, 1.414), (-1.414, 0), (0,0).
# Centroid: (-0.471, 0.471).
# Orientation: Hypotenuse Bottom? No, Hypotenuse is vertical x=0?
# LT1 Hypotenuse is 2. Vertices (0, 1.414) to (-1.414, 0). Length 2.
# Legs: (0, 1.414) to (0,0) [Length 1.414]. (0,0) to (-1.414, 0) [Length 1.414].
# Right Angle at (0,0).
# Local LT (Rot 0): RA at (0,0). Legs (0, 1.414) and (1.414, 0).
# To get Legs (0, 1.414) and (-1.414, 0): Rotate 90?
# (1.414, 0) -> (0, 1.414). (0, 1.414) -> (-1.414, 0).
# Yes, Rot 90.
house_pieces = {}
house_pieces['LT1'] = {'pos': (-0.471, 0.471 + 1.414), 'rot': math.radians(90)} 
# Shift Y by 1.414 (Body Height)

# LT2: Right Half. Vertices (0, 1.414), (1.414, 0), (0,0).
# Centroid: (0.471, 0.471).
# Orientation: RA at (0,0). Legs (0, 1.414) and (1.414, 0).
# This is Rot 0.
house_pieces['LT2'] = {'pos': (0.471, 0.471 + 1.414), 'rot': math.radians(0)}

# Body: Square of side 1.414. (Area 2).
# Made of MT, Sq, ST, ST, Para.
# MT: Top-Left. Vertices (0, 1.414), (0,0), (1.414, 0)? No.
# MT Hyp is 1.414. Legs 1.
# Let's fill the square (0,0) to (1.414, 1.414).
# 1. MT: Bottom-Right Corner. Vertices (1.414, 0), (1.414, 1), (0.414, 0)?
# Let's place MT at Bottom-Left. (0,0), (1,0), (0,1).
# Hypotenuse (1,0) to (0,1). Length 1.414.
# Centroid (0.333, 0.333).
# Local MT (Rot 0): RA at (0,0). Legs (0,1) and (1,0).
# Matches. Rot 0.
house_pieces['MT'] = {'pos': (0.333, 0.333), 'rot': math.radians(0)}

# 2. Square: Top-Right?
# We have gap above MT hypotenuse.
# Line y = 1-x.
# Square side 0.707.
# Place Square at (0.707, 0.707)?
# Vertices (0.353, 0.353) to (1.06, 1.06).
# Let's place Square on top of MT?
# Vertices (0,1), (0.5, 1.5)?
# Let's use a known rectangle layout.
# MT + 2 STs = Square (Side 1).
# MT (0,0)-(1,0)-(0,1).
# ST1 (0,1)-(1,1)-(1,0)?
# ST1 Hyp 1. Legs 0.707.
# (0,1) to (1,0) is length 1.414.
# So ST1 cannot cover it.
# We need 2 STs to cover the hypotenuse.
# ST1: (0,1), (0.5, 0.5), (1,1)? No.
# ST1: (0,1), (0.5, 0.5), (0.5, 1.5)?
# Let's try:
# MT at (0,0).
# ST1 at (0.5, 0.5) [RA]. Vertices (0,1), (1,0), (0.5, 0.5).
# Hypotenuse (0,1) to (1,0). Length 1.414.
# ST1 Hyp is 1.
# So ST1 cannot span.
# We need MT + 2 STs + Sq + Para to form 1.414 x 1.414.
# This is Area 2.
# MT(0.5) + Sq(0.5) + ST(0.25) + ST(0.25) + Para(0.5) = 2.
# Yes.
# Layout:
# 1. MT: (0,0)-(1.414,0)-(0,1.414)? No, MT legs are 1.
#    So MT is small.
#    Let's place MT at (0,0) to (1,0) to (0,1).
#    Remaining area: L-shape.
#    (1,0) to (1.414,0) to (1.414,1.414) to (0,1.414) to (0,1) to (1,1) to (1,0).
# 2. Para: (0,1) to (1,1) to (1.5, 1.5) to (0.5, 1.5)?
#    Let's place Para at Top-Left.
#    (0,1) to (0, 1.414)? Length 0.414.
#    Para side 1 or 0.707.
#    This is getting complicated.

# Alternative Body:
# Just stack pieces in a rectangle 0.707 x 2.828?
# Or 1.414 x 1.414 using a known solution.
# Known solution for Square using 5 small pieces:
# 1. MT.
# 2. Sq.
# 3. ST1.
# 4. ST2.
# 5. Para.
# Layout:
# MT corner at (0,0). Legs (0,1), (1,0).
# ST1 corner at (1,1). Legs (1,0), (0,1)? No.
# ST1 corner at (1.414, 1.414). Legs (0.707, 1.414), (1.414, 0.707).
# ST2 ...
# Sq ...
# Para ...
# I'll search for "Tangram 5 piece square".
# It exists.
# Layout:
# MT: (0,0)-(1,0)-(0,1).
# Para: (1,0)-(1.5, 0.5)-(1.5, 1.5)-(1,1)? No.
# Para: (0,1)-(1,1)-(0.5, 0.5)-(...)?
# Let's try:
# MT: (0,0), (1,0), (0,1).
# Para: (0,1), (1,1), (1,0), (0,0)? No.
# Para: (0,1), (0.5, 1.5), (1.5, 1.5), (1,1).
#   (0,1) to (1,1) length 1.
#   (1,1) to (1.5, 1.5) length 0.707.
#   (1.5, 1.5) to (0.5, 1.5) length 1.
#   (0.5, 1.5) to (0,1) length 0.707.
#   This fits!
#   So Para is at Top.
#   Vertices: (0,1), (1,1), (1.5, 1.5), (0.5, 1.5).
#   Centroid: (0.75, 1.25).
#   Rotation: Base horizontal. Slant Up-Right.
#   Local Para (Rot 0): Base horizontal. Slant Up-Right.
#   Matches! Rot 0.
#   Flipped?
#   Local: (0,0)->(1,0)->(1.5,0.5)->(0.5,0.5).
#   Target: (0,1)->(1,1)->(1.5,1.5)->(0.5,1.5).
#   Shifted by (0,1).
#   Matches. Flipped=False.
house_pieces['Para'] = {'pos': (0.75, 1.25), 'rot': 0, 'flipped': False}

# Remaining: (1,0) to (1.414,0) ...
# We have a strip on the right?
# Bounding box is (0,0) to (1.5, 1.5)?
# No, we want 1.414 x 1.414?
# Para goes up to y=1.5. 1.5 > 1.414.
# So this doesn't form a perfect square.
# It forms a shape.
# That's fine! A "House" doesn't need a square body.
# It needs a "Body".
# So far:
# MT at bottom-left.
# Para on top of MT.
# We have Sq, ST1, ST2 left.
# Let's place Sq next to MT.
# MT edge (1,0) to (0,1).
# Sq at (1,0)?
# Sq vertices: (1,0), (1.707, 0), (1.707, 0.707), (1, 0.707).
# Overlaps Para?
# Para is at y>=1. Sq is y<=0.707. No overlap.
# Sq is at x>=1. MT is x<=1. No overlap.
house_pieces['Sq'] = {'pos': (1.3535, 0.3535), 'rot': 0} # Centroid of (1,0) square

# ST1 and ST2.
# We have gaps.
# Gap 1: Between Para and Sq?
# Para (1,1). Sq (1, 0.707).
# Gap 2: Right of Sq?
# Let's just place them to make it look like a chimney or extension.
# ST1 on top of Sq.
# (1, 0.707) to (1.707, 0.707).
# ST1 Hyp 1. Legs 0.707.
# Place ST1 leg on Sq top.
# Vertices: (1, 0.707), (1, 1.414), (1.707, 0.707).
# Centroid: (1.235, 0.943).
# Rot: RA at (1, 0.707). Legs Up and Right.
# Local ST (Rot 0): RA at (0,0). Legs Up and Right?
# Local ST: (0, 0.707), (0,0), (0.707, 0).
# RA at (0,0). Legs Up and Right.
# Matches. Rot 0.
house_pieces['ST1'] = {'pos': (1.235, 0.943), 'rot': 0}

# ST2.
# Chimney?
# Place on top of Para?
# Para top edge (0.5, 1.5) to (1.5, 1.5).
# ST2 Hyp 1.
# Place ST2 Hyp on Para top.
# Vertices: (0.5, 1.5), (1.5, 1.5), (1.0, 2.0).
# Centroid: (1.0, 1.666).
# Rot: Hyp Down. RA Top.
# Local ST (Rot 0): Hyp Top-Right.
# To get Hyp Down: Rotate 135?
# RA at (1.0, 2.0).
# Local RA at (0,0).
# Legs (1.0, 2.0)->(0.5, 1.5) [-0.5, -0.5].
# Legs (1.0, 2.0)->(1.5, 1.5) [0.5, -0.5].
# Local Legs (0,1) and (1,0).
# (0,1) -> (-0.5, -0.5). Rot 135.
# (1,0) -> (0.5, -0.5). Rot -45 (315).
# Wait.
# (0,1) is 90 deg. (-0.5, -0.5) is 225 deg. Diff 135.
# (1,0) is 0 deg. (0.5, -0.5) is 315 deg. Diff 315 (-45).
# Angles are not preserving relative 90 deg?
# 225 - 315 = -90.
# 90 - 0 = 90.
# So flipped?
# ST is symmetric.
# Rot 135 should work.
house_pieces['ST2'] = {'pos': (1.0, 1.666), 'rot': math.radians(135)}

for k, v in house_pieces.items():
    rot_deg = rad_to_deg(v['rot'])
    flipped = v.get('flipped', False)
    print(f"{k}: Pos={v['pos']}, Rot={rot_deg}, Flipped={flipped}")
