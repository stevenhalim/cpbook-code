open Printf

module Option = struct
  let map f = function
    | Some x -> Some (f x)
    | None -> None
  let fold ifnone f = function
    | Some x -> f x
    | None -> ifnone
  let foreach f = fold () f
end

(* From points_lines.ml *)

let eps = 1e-9
let near x y = abs_float (x -. y) < eps
let pi = Float.pi

let deg_to_rad d = d *. pi /. 180.
let rad_to_deg r = r *. 180. /. pi

type point = { x: float; y: float }
let point (x, y) = { x; y }

let dist a b = hypot (a.x -. b.x) (a.y -. b.y)

type vector = Vector of float * float

let to_vec a b = Vector(b.x -. a.x, b.y -. a.y)
let scale (Vector(a, b)) s = Vector(a *. s, b *. s)
let translate {x; y} (Vector(a, b)) = point(x +. a, y +. b)
let dot (Vector(a1, b1)) (Vector(a2, b2)) = a1 *. a2 +. b1 *. b2
let norm v = sqrt (dot v v)
let cross (Vector(a1, b1)) (Vector(a2, b2)) = a1 *. b2 -. a2 *. b1

let ccw p q r = cross (to_vec p q) (to_vec p r) > eps
let collinear p q r = near (cross (to_vec p q) (to_vec p r)) 0.

module Line : sig
  type line
  val through_points    : point -> point -> line
  val are_parallel      : line -> line -> bool
  val intersect         : line -> line -> point option
  val to_string         : line -> string
end = struct
  (** ax + by + c = 0 *)
  type line = { a: float; b: float; c: float }

  let through_points p1 p2 =
    if near p1.x p2.x then { a = 1.; b = 0.; c = -. p1.x }
    else
      let a = -. (p1.y -. p2.y) /. (p1.x -. p2.x) in
      { a; b = 1.; c = -. a *. p1.x -. p1.y }

  let are_parallel l1 l2 = near l1.a l2.a && near l1.b l2.b

  let are_same l1 l2 = are_parallel l1 l2 && near l1.c l2.c

  let intersect l1 l2 =
    if are_parallel l1 l2 then None
    else
      let x = (l2.b *. l1.c -. l1.b *. l2.c) /. (l2.a *. l1.b -. l1.a *. l2.b) in
      let y =
        if not (near l1.b 0.) then -. (l1.a *. x +. l1.c)
        else -. (l2.a *. x +. l2.c) in
      Some (point (x, y))
  
  let to_string line =
    sprintf "%.2f * x + %.2f * y + %.2f = 0.00" line.a line.b line.c
end

(* End from points_lines.ml *)

type triangle = Triangle of point * point * point
type circle = { center: point; radius: float } 

let sqr x = x *. x

let can_form_triangle x y z = x +. y > z && y +. z > x && x +. z > y

(* Returns: 0 inside / 1 border / 2 outside *)
let inside_circle {x; y} { center; radius } =
  let dx, dy = x -. center.x, y -. center.y in
  compare (dx *. dx +. dy *. dy) (radius *. radius) + 1

let perimeter (Triangle(a, b, c)) = dist a b +. dist b c +. dist c a

let heron ab bc ca =
  let s = (ab +. bc +. ca) /. 2. in
  sqrt (s *. (s -. ab) *. (s -. bc) *. (s -. ca))

let area (Triangle(a, b, c)) = 0.5 *. abs_float (cross (to_vec a b) (to_vec a c))

let r_incircle triangle = area triangle /. (0.5 *. perimeter triangle)

let incircle (Triangle(a, b, c) as t) =
  let radius = r_incircle t in
  if radius < eps then None else
  let bisector a b c =
    let ratio = dist a b /. dist a c in
    let p = translate b (scale (to_vec b c) (ratio /. (1. +. ratio))) in
    Line.through_points a p in
  Line.intersect (bisector a b c) (bisector b a c)
    |> Option.map (fun center -> { center; radius })

let r_circumcircle (Triangle(a, b, c) as t) =
  dist a b *. dist b c *. dist c a /. (4. *. area t)

let circumcircle (Triangle(p1, p2, p3)) =
  let a, b = p2.x -. p1.x, p2.y -. p1.y in
  let c, d = p3.x -. p1.x, p3.y -. p1.y in
  let e = a *. (p1.x +. p2.x) +. b *. (p1.y +. p2.y) in
  let f = c *. (p1.x +. p3.x) +. d *. (p1.y +. p3.y) in
  let g = 2. *. (a *. (p3.y -. p2.y) -. b *. (p3.x -. p2.x)) in
  if near g 0. then None else
  let center = point((d *. e -. b *. f) /. g, (a *. f -. c *. e) /. g) in
  Some { center; radius = dist p1 center }

let in_circumcircle triangle p =
  circumcircle triangle |> Option.fold false (fun circle ->
    inside_circle p circle = 0)

let () =
  let t = Triangle(point(0., 0.), point(4., 0.), point(4., 3.)) in
  printf "Area = %.2f\n" (area t);

  let to_string {x; y} = sprintf "(%.2f, %.2f)" x y in
  
  incircle t |> Option.foreach (fun circle ->
    printf "R1 (radius of incircle) = %.2f\n" circle.radius;
    printf "Center = %s\n" (to_string circle.center));
  
  circumcircle t |> Option.foreach (fun circle ->
    printf "R1 (radius of circumcircle) = %.2f\n" circle.radius;
    printf "Center = %s\n" (to_string circle.center));

  [point(2.0, 1.0); point(2.0, 3.9); point(2.0, -1.1)]
    |> List.iter (fun point ->
      printf "%s inside circumCircle? %b\n"
        (to_string point)
        (in_circumcircle t point);  
    )
