open Printf

type 'a point = Point of 'a * 'a

type 'a circle = { c: 'a point; r: 'a } 

let pi = Float.pi
let sqr x = x *. x
let deg_to_rad d = d *. pi /. 180.

let inside_circle (Point(x, y)) { c=Point(cx, cy); r } =
  let dx, dy = x - cx, y - cy in
  compare (dx * dx + dy * dy) (r * r) + 1 (* 0 inside / 1 border / 2 outside *)

(** Returns the center of a circle with radius r and goes through 2 points.
    To get the other center, reverse p1 and p2 *)
let circle_2pts_rad (Point(x1, y1)) (Point(x2, y2)) r =
  let d2 = sqr (x1 -. x2) +. sqr (y1 -. y2) in
  let det = sqr r /. d2 -. 0.25 in
  if det < 0. then None else
  let h = sqrt det in
  let cx = (x1 +. x2) *. 0.5 +. (y1 -. y2) *. h in
  let cy = (y1 +. y2) *. 0.5 +. (x1 -. x2) *. h in
  Some (Point(cx, cy))

let () =
  let circle = { c = Point(2, 2); r = 7 } in
  let inside = Point(8, 2) in printf "%d\n" (inside_circle inside circle);
  let border = Point(9, 2) in printf "%d\n" (inside_circle border circle);
  let outside = Point(10, 2) in printf "%d\n" (inside_circle outside circle);

  let r = float_of_int circle.r in
  let d = r *. 2. in
  let c = d *. pi in
  let area = pi *. sqr r in
  printf "Diameter = %.2f\n" d;
  printf "Circumference (Perimeter) = %.2f\n" c;
  printf "Area of circle = %.2f\n" area;

  printf "Length of arc   (central angle = 60 degrees) = %.2f\n"
    (60.0 /. 360.0 *. c);
  printf "Length of chord (central angle = 60 degrees) = %.2f\n"
    (sqrt (2. *. sqr r *. (1. -. cos (deg_to_rad 60.0))));
  printf "Area of sector  (central angle = 60 degrees) = %.2f\n"
    (60.0 /. 360.0 *. area);

  let p1 = Point(0., 0.) in
  let p2 = Point(0., -1.) in
  match circle_2pts_rad p1 p2 2., circle_2pts_rad p2 p1 2. with
  | Some (Point(x1, y1)), Some (Point(x2, y2)) ->
    printf "One of the center is (%.2f, %.2f)\n" x1 y1;
    printf "The other center  is (%.2f, %.2f)\n" x2 y2;
  | _ -> assert false
