# MTFP

**Format of input txt file:**

Suppose we have two projects and individuals having three different skills are required:

========================================================================================

Weight of project-1

Skill_req_1  Skill_req_2 Skill_req_3

Weight of project-2

Skill_req_1 Skill_req_2 Skill_req_3

Number of individual for Skill-1

< available individuals along with their unique id >

Number of individual for Skill-2

< available individuals along with their unique id >

Number of individual for Skill-3

< available individuals along with their unique id >

=======================================================================================

Example of Sociometry matrix is provided inside the folder **"Sociometry_Example" **

**Format of Sociometry:**

=======================================================================================

If total individual of n then 

Matrix of size nxn containing positive, negative, and neutral relationship between individuals

Number of Positive relation 

Number of Negative relation

An optimized team having 100% efficiency

=======================================================================================

**Codes:** 

(1) **mtfp_ga.c** Contains the implemetation of MTFP using proposed GA-based approach.

(2) **mtfp_vns.c** Contains the implementation of MTFP using Variable Neigborhood Search. 

========================================================================================

**Cite this paper:**

**V. S. Baghel** and S. Durga Bhavani, "Multiple team formation using an evolutionary approach," In Proceedings of Eleventh International Conference on Contemporary Computing (IC3), pp 1-6, 2-4 August 2018, Noida, India.
