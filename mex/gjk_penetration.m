% GJK_PENETRATION Compute penetration depth, separation direction, and
% contact position between two intersecting convex hulls using GJK + EPA
% (Expanding Polytope Algorithm).
%
% [depth,dir,pos] = gjk_penetration(V1,F1,V2,F2)
%
% Inputs:
%   V1  #V1 by 3 list of vertex positions of first convex hull
%   F1  #F1 by 3 list of triangle indices into V1
%   V2  #V2 by 3 list of vertex positions of second convex hull
%   F2  #F2 by 3 list of triangle indices into V2
% Outputs:
%   depth  scalar penetration depth ([] if not intersecting)
%   dir    1 by 3 unit direction to move V2 to resolve penetration
%            ([] if not intersecting)
%   pos    1 by 3 contact point position in world space
%            ([] if not intersecting)
%
% See also: gjk_intersect, mpr_intersect, mpr_penetration
