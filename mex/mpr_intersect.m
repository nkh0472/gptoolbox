% MPR_INTERSECT Test whether two convex hulls intersect using the
% Minkowski Portal Refinement (MPR) algorithm.
%
% I = mpr_intersect(V1,F1,V2,F2)
%
% Inputs:
%   V1  #V1 by 3 list of vertex positions of first convex hull
%   F1  #F1 by 3 list of triangle indices into V1
%   V2  #V2 by 3 list of vertex positions of second convex hull
%   F2  #F2 by 3 list of triangle indices into V2
% Outputs:
%   I  true if the two convex hulls intersect, false otherwise
%
% See also: mpr_penetration, gjk_intersect, gjk_penetration
