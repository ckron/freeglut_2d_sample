

## exec
1. cd ./freeglut_2d_sample
2. docker-compose up -d --build
3. docker-compose exec glut2d-demo bash
4. cd /root/workspace/src
5. g++ -Wall -Weffc++ main.cpp -lglut -lGLU -lGL -o res.out
6. ./res.out