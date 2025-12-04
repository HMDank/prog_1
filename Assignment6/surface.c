#include "base.h"
#define M_PI 3.14159265358979323846 /* pi */
typedef enum Tag { TCylinder, TSphere, TCuboid } Tag;
struct Cylinder {
  double r, h; // A = 2 pi r^2 + 2 pi r h
};
struct Sphere {
  double r; // A = 4 pi r^2
};
struct Cuboid {
  double a, b, c; // A = 2ab + 2ac + 2bc
};
struct GeomObject {
  Tag tag;
  union {
    struct Cylinder cylinder;
    struct Sphere sphere;
    struct Cuboid cuboid;
  } u;
};
typedef struct Cylinder Cylinder;
typedef struct Sphere Sphere;
typedef struct Cuboid Cuboid;
typedef struct GeomObject GeomObject;

GeomObject make_cylinder(double r, double h) {
  GeomObject o = {0};
  o.tag = TCylinder;
  o.u.cylinder.r = r;
  o.u.cylinder.h = h;
  return o;
}
GeomObject make_sphere(double r) {
  GeomObject o = {0};
  o.tag = TSphere;
  o.u.sphere.r = r;
  return o;
}
GeomObject make_cuboid(double a, double b, double c) {
  GeomObject o = {0};
  o.tag = TCuboid;
  o.u.cuboid.a = a;
  o.u.cuboid.b = b;
  o.u.cuboid.c = c;
  return o;
}
double surface_area(GeomObject o);
void surface_area_test(void) {
  test_within_d(surface_area(make_sphere(2)), 4 * M_PI * 2 * 2, 1e-6);
  test_within_d(surface_area(make_cuboid(2, 3, 4)),
                2 * 2 * 3 + 2 * 2 * 4 + 2 * 3 * 4, 1e-6);
  test_within_d(surface_area(make_cylinder(3, 4)),
                2 * M_PI * 3 * 3 + 2 * M_PI * 3 * 4, 1e-6);
}
double surface_area(GeomObject o) {
  switch (o.tag) {
  case TSphere: {
    double r = o.u.sphere.r;
    return 4.0 * M_PI * r * r;
  }
  case TCuboid: {
    double a = o.u.cuboid.a;
    double b = o.u.cuboid.b;
    double c = o.u.cuboid.c;
    return 2.0 * a * b + 2.0 * a * c + 2.0 * b * c;
  }
  case TCylinder: {
    double r = o.u.cylinder.r;
    double h = o.u.cylinder.h;
    return 2.0 * M_PI * r * r + 2.0 * M_PI * r * h;
  }
  default:
    return 0.0;
  }
}
int main(void) {
  surface_area_test();
  return 0;
}