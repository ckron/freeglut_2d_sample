

## exec
1. cd ./freeglut_2d_sample
2. docker-compose up -d --build
3. docker-compose exec glut2d-demo bash
4. cd /root/workspace/src
5. g++ -Wall -Weffc++ main.cpp -lglut -lGLU -lGL -o res.out
6. ./res.out

### reference
1. https://www.webcyou.com/?p=9639
2. http://www.oit.ac.jp/is/L231/pukiwiki/index.php?%E6%84%9F%E8%A6%9A%E3%83%A1%E3%83%87%E3%82%A3%E3%82%A2%E7%A0%94%E7%A9%B6%E5%AE%A4/OpenGL/%E3%83%86%E3%82%AF%E3%82%B9%E3%83%81%E3%83%A3%E3%83%9E%E3%83%83%E3%83%94%E3%83%B3%E3%82%B0
3. https://marina.sys.wakayama-u.ac.jp/~tokoi/?date=20050614