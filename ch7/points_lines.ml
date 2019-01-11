open Printf

let eps = 1e-9
let near x y = abs_float (x -. y) < eps
let pi = Float.pi

let deg_to_rad d = d *. pi /. 180.
let rad_to_deg r = r *. 180. /. pi

type point = { x: float; y: float }
let point (x, y) = { x; y }

let dist a b = hypot (a.x -. b.x) (a.y -. b.y)

let rotate {x; y} degree =
  let rad = deg_to_rad degree in
  let sin = sin rad in
  let cos = cos rad in
  point(x *. cos -. y *. sin, x *. sin +. y *. cos)

type vector = Vector of float * float

let to_vec a b = Vector(b.x -. a.x, b.y -. a.y)
let scale (Vector(a, b)) s = Vector(a *. s, b *. s)
let translate {x; y} (Vector(a, b)) = point(x +. a, y +. b)
let dot (Vector(a1, b1)) (Vector(a2, b2)) = a1 *. a2 +. b1 *. b2
let norm v = sqrt (dot v v)
let cross (Vector(a1, b1)) (Vector(a2, b2)) = a1 *. b2 -. a2 *. b1

let angle a o b =
  let oa = to_vec o a in
  let ob = to_vec o b in
  acos (dot oa ob /. (norm oa *. norm ob))

let ccw p q r = cross (to_vec p q) (to_vec p r) > eps
let collinear p q r = near (cross (to_vec p q) (to_vec p r)) 0.

module Line : sig
  type line
  val through_points    : point -> point -> line
  val from_point_slope  : point -> float -> line
  val are_parallel      : line -> line -> bool
  val are_same          : line -> line -> bool
  val intersect         : line -> line -> point option
  val closest_point     : line -> point -> point
  val reflection_point  : line -> point -> point
  val to_string         : line -> string
end = struct
  (** ax + by + c = 0 *)
  type line = { a: float; b: float; c: float }

  let through_points p1 p2 =
    if near p1.x p2.x then { a = 1.; b = 0.; c = -. p1.x }
    else
      let a = -. (p1.y -. p2.y) /. (p1.x -. p2.x) in
      { a; b = 1.; c = -. a *. p1.x -. p1.y }

  let from_point_slope {x; y} m =
    let a, b = -. m, 1. in
    { a; b; c = -. ((a *. x) +. (b *. y)) }

  type line2 = { m: float; c: float }

  let through_points2 p1 p2 =
    if near p1.x p2.x then None
    else
      let m = (p1.y -. p2.y) /. (p1.x -. p2.x) in
      let c = p1.y -. m *. p1.x in
      Some { m; c }

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
  
  let closest_point l ({x; y} as p) =
    if near l.b 0. then point(-. l.c, y) else
    if near l.a 0. then point(x, -. l.c) else
    let perpendicular = from_point_slope p (1. /. l.a) in
    match intersect l perpendicular with
    | Some q -> q
    | None -> assert false
  
  let reflection_point l p =
    let q = closest_point l p in
    let v = to_vec p q in
    translate q v

  let to_string line =
    sprintf "%.2f * x + %.2f * y + %.2f = 0.00" line.a line.b line.c
end

let altitude p a b : float * point =
  let ap = to_vec a p in
  let ab = to_vec a b in
  let u = dot ap ab /. dot ab ab in
  let c = translate a (scale ab u) in
  dist p c, c

let dist_to_segment p a b : float * point =
  let ap = to_vec a p in
  let ab = to_vec a b in
  let u = dot ap ab /. dot ab ab in
  if u < 0. then dist p a, a else
  if u > 1. then dist p b, b else
  altitude p a b

let () =
  (* sorting points demo *)
  let p =
    [ point(2., 2.)
    ; point(4., 3.)
    ; point(2., 4.)
    ; point(6., 6.)
    ; point(2., 6.)
    ; point(6., 5.)] in
  p
    |> List.sort (fun p1 p2 ->
      if near p1.x p2.x then compare p1.y p2.y else compare p1.x p2.x)
    |> List.iter (fun {x; y} -> printf "(%.2f, %.2f)\n" x y);
  
  (* the positions of these 7 points (0-based indexing)
  6   P4      P3  P6
  5           P5
  4   P2
  3       P1
  2   P0
  1
  0 1 2 3 4 5 6 7 8 *)
  let p = p @ [point(8., 6.)] |> Array.of_list in
  printf "Euclidean distance between P[0] and P[5] = %.2f\n" (dist p.(0) p.(5));

  let l1 = Line.through_points p.(0) p.(1) in
  let l2 = Line.through_points p.(0) p.(2) in
  let l3 = Line.through_points p.(2) p.(3) in
  let l4 = Line.through_points p.(2) p.(4) in
  printf "%s\n" (Line.to_string l1);
  printf "%s\n" (Line.to_string l2);
  let bool_to_int = function true -> 1 | false -> 0 in
  printf "l1 & l2 are parallel? %d\n" (Line.are_parallel l1 l2 |> bool_to_int);
  printf "l1 & l3 are parallel? %d\n" (Line.are_parallel l1 l3 |> bool_to_int);
  printf "l1 & l2 are the same? %d\n" (Line.are_same l1  l2 |> bool_to_int);
  printf "l2 & l4 are the same? %d\n" (Line.are_same l2  l4 |> bool_to_int);

  (match Line.intersect l1 l2 with
  | Some {x; y} ->
    printf "l1 & l2 are intersect? 1, at (%.2f, %.2f)\n" x y
  | None -> ());

  let fmt = format_of_string ": (%.2f, %.2f), dist = %.2f\n" in
  let d, {x; y} = altitude p.(0) p.(2) p.(3) in
  printf ("Closest point from P[0] to line         (P[2]-P[3])" ^^ fmt) x y d;
  let ({x; y} as q) = Line.closest_point l3 p.(0) in
  printf ("Closest point from P[0] to line V2      (P[2]-P[3])" ^^ fmt) x y (dist p.(0) q);
  
  [(0, 2, 3); (1, 2, 3); (6, 2, 3)] |> List.iter (fun (i, j, k) ->
    let d, {x; y} = dist_to_segment p.(i) p.(j) p.(k) in
    printf ("Closest point from P[%d] to line SEGMENT (P[%d]-P[%d])" ^^ fmt) i j k x y d
  );
  
  let {x; y} = Line.reflection_point l4 p.(1) in
  printf "Reflection point from P[1] to line      (P[2]-P[4]): (%.2f, %.2f)\n" x y;

  [(0, 4, 3); (0, 2, 1); (4, 3, 6)] |> List.iter (fun (i, j, k) ->
    printf "Angle P[%d]-P[%d]-P[%d] = %.2f\n" i j k (rad_to_deg (angle p.(i) p.(j) p.(k)));
  );

  [(0, 2, 3); (0, 3, 2)] |> List.iter (fun (i, j, k) ->
    printf "P[%d], P[%d], P[%d] form A left turn? %d\n" i j k (ccw p.(i) p.(j) p.(k) |> bool_to_int)
  );

  [(0, 2, 3); (0, 2, 4)] |> List.iter (fun (i, j, k) ->
    printf "P[%d], P[%d], P[%d] are collinear? %d\n" i j k (collinear p.(i) p.(j) p.(k) |> bool_to_int)
  );

  let p, q, r = point(3., 7.), point(11., 13.), point(35., 30.) in
  printf "r is on the %s of line p-r\n" (if ccw p q r then "left" else "right");

  (* the positions of these 6 points
     E<--  4
           3       B D<--
           2   A C
           1
  -4-3-2-1 0 1 2 3 4 5 6
          -1
          -2
   F<--   -3 *)
  let a = point(2., 2.) in
  let b = point(4., 3.) in
  let c = point(3., 2.) in
  let v = to_vec a b in
  
  (* translation *)
  let d = translate c v in
  let point_to_string {x; y} = sprintf "(%.2f, %.2f)" x y in
  printf "D = %s\n" (point_to_string d);
  let e = translate c (scale v 0.5) in
  printf "E = %s\n" (point_to_string e);
  
  (* rotation *)
  printf "B = %s\n" (point_to_string b);
  let f = rotate b 90. in
  printf "F = %s\n" (point_to_string f);
  let g = rotate b 180. in
  printf "G = %s\n" (point_to_string g)
