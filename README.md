GPGPU Iterative Closest Point Algorithm
=======================================

## Steps
1. get_correspondence_indices()
2. center_data()
3. compute_cross_covariance()
4. icp_svd()
5. jacobian, error, dr, R, etc
6. icp_least_squares() + prepare_system()
7. compute_normals() + plot_normals()
8. RotationMatrix()
9. icp_normal() + prepare_system_normals()
10. kernel()

Bon Chance


## Resource

Matlab implementation
http://www.sci.utah.edu/~shireen/pdfs/tutorials/Elhabian_ICP09.pdf

A detailed Python implementation (Jupyter notebook)
https://github.com/niosus/notebooks/blob/master/icp.ipynb

A great visualization tool for 3D point clouds
https://www.paraview.org/

The Point Cloud Library (PCL)
https://pointclouds.org/

PCL Tutorial: How to use iterative closest point
https://pcl.readthedocs.io/projects/tutorials/en/latest/iterative_closest_point.html


## GROUPE F : La WatiZamen Team
```
Chow William
 DoriAn Vinai
   AnToine Coulon
    VIncent Payet
   LaBonne
```
