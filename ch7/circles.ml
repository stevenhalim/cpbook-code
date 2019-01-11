open Printf

type 'a point = { x: 'a; y: 'a }
let point (x, y) = { x; y }

type 'a circle = { center: 'a point; radius: 'a } 

let pi = Float.pi
let sqr x = x *. x
let deg_to_rad d = d *. pi /. 180.

(* Returns: 0 inside / 1 border / 2 outside *)
let inside_circle {x; y} { center; radius } =
  let dx, dy = x - center.x, y - center.y in
  compare (dx * dx + dy * dy) (radius * radius) + 1

(** Returns the center of a circle with radius r and goes through 2 points.
    To get the other center, reverse p1 and p2 *)
let circle_2pts_rad p1 p2 r =
  let d2 = sqr (p1.x -. p2.x) +. sqr (p1.y -. p2.y) in
  let det = sqr r /. d2 -. 0.25 in
  if det < 0. then None else
  let h = sqrt det in
  let cx = (p1.x +. p2.x) *. 0.5 +. (p1.y -. p2.y) *. h in
  let cy = (p1.y +. p2.y) *. 0.5 +. (p1.x -. p2.x) *. h in
  Some (point(cx, cy))

let () =
  let circle = { center = point(2, 2); radius = 7 } in
  let inside = point(8, 2) in printf "%d\n" (inside_circle inside circle);
  let border = point(9, 2) in printf "%d\n" (inside_circle border circle);
  let outside = point(10, 2) in printf "%d\n" (inside_circle outside circle);

  let r = float_of_int circle.radius in
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

  let p1 = point(0., 0.) in
  let p2 = point(0., -1.) in
  match circle_2pts_rad p1 p2 2., circle_2pts_rad p2 p1 2. with
  | Some p1, Some p2 ->
    printf "One of the center is (%.2f, %.2f)\n" p1.x p1.y;
    printf "The other center  is (%.2f, %.2f)\n" p2.x p2.y;
  | _ -> assert false
