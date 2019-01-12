open Printf

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

let angle a o b =
  let oa = to_vec o a in
  let ob = to_vec o b in
  acos (dot oa ob /. (norm oa *. norm ob))

let collinear p q r = near (cross (to_vec p q) (to_vec p r)) 0.

(* End from points_lines.ml *)

let ccw p q r =
  let s = cross (to_vec p q) (to_vec p r) in
  if near s 0. then 0 else
  if s > 0. then 1 else -1

module Polygon : sig
  type t = point array
  val of_points         : point list -> t
  val points            : t -> point list
  val perimeter         : t -> float
  val area              : t -> float
  val area_alternative  : t -> float
  val is_convex         : t -> bool
  val in_polygon        : t -> point -> bool
  val cut_polygon       : t -> point -> point -> t
  val convex_hull       : point list -> t
end = struct
  (** Counter-clockwise order, the last point is the same as the first point *)
  type t = point array

  let of_points ps =
    let n = List.length ps in
    let arr = Array.make (n + 1) (point(0., 0.)) in
    ps |> List.iteri (fun i v -> arr.(i) <- v);
    arr.(n) <- arr.(0);
    arr
  
  let points p = p |> Array.to_list |> List.tl

  let perimeter p =
    let n = Array.length p in
    let result = ref 0. in
    for i = 0 to n - 2 do
      let a, b = p.(i), p.(i + 1) in
      result := !result +. dist a b
    done;
    !result

  let area p =
    let n = Array.length p in
    let result = ref 0. in
    for i = 0 to n - 2 do
      let a, b = p.(i), p.(i + 1) in
      result := !result +. (a.x *. b.y -. b.x *. a.y)
    done;
    abs_float !result /. 2.0

  let area_alternative p =
    let n = Array.length p in
    let o = point(0., 0.) in
    let result = ref 0. in
    for i = 0 to n - 2 do
      let a, b = p.(i), p.(i + 1) in
      result := !result +. cross (to_vec o a) (to_vec o b)
    done;
    abs_float !result /. 2.0

  let is_convex p =
    let n = Array.length p in
    if n <= 3 then false else begin
      let l, r = ref false, ref false in
      for i = 0 to n - 2 do
        let a, b, c = p.(i), p.(i + 1), p.(if i + 2 = n then 1 else i + 2) in
        let s = ccw a b c in
        if s = 1 then l := true else
        if s = -1 then r := true
      done;
      not (!l && !r)
    end
  
  let in_polygon p point =
    let n = Array.length p in
    if n <= 3 then false else begin
      let sum = ref 0. in
      let border = ref false in
      for i = 0 to n - 2 do
        let a, b = p.(i), p.(i + 1) in
        let side = ccw point a b in
        if side = 1 then
          sum := !sum +. angle a point b
        else if side = -1 then sum := !sum -. angle a point b
        else border := true
      done;
      !border || abs_float !sum > pi
    end

  let line_intersect_segment p q r s =
    let a = s.y -. r.y in
    let b = r.x -. s.x in
    let c = s.x *. r.y -. r.x *. s.y in
    let u = abs_float (a *. p.x +. b *. p.y +. c) in
    let v = abs_float (a *. q.x +. b *. q.y +. c) in
    point((p.x *. v +. q.x *. u) /. (u+.v), (p.y *. v +. q.y *. u) /. (u+.v))

  let cut_polygon p a b =
    let p' = ref [] in
    let n = Array.length p in
    for i = 0 to n - 1 do
      let left1 = cross (to_vec a b) (to_vec a p.(i)) in
      let left2 =
        if i <> n - 1 then cross (to_vec a b) (to_vec a p.(i + 1))
        else 0. in
      if left1 > -. eps then p' := p.(i) :: !p'; (* Q[i] is on the left of ab *)
      if left1 *. left2 < -.eps then   (* edge (Q[i], Q[i+1]) crosses line ab *)
        p' := line_intersect_segment p.(i) p.(i + 1) a b :: !p';
    done;
    if List.length !p' > 0 then begin
      let last = !p' |> List.fold_left (fun _ x -> x) (point(0., 0.)) in
      if last <> (List.hd !p') then p' := last :: !p'
    end;
    !p' |> List.rev |> Array.of_list

  (** Andrew's algorithm *)
  let convex_hull points =
    let points = points |> Array.of_list in
    points |> Array.sort (fun a b ->
      compare (a.x, a.y) (b.x, b.y));
    let n = Array.length points in
    let hull = Array.make (2 * n) (point(0., 0.)) in
    let k = ref 0 in
    for i = 0 to n - 1 do
      while !k >= 2 && ccw hull.(!k-2) hull.(!k-1) points.(i) <= 0 do
        decr k
      done;
      hull.(!k) <- points.(i);
      incr k
    done;
    let t = !k + 1 in
    for i = n - 2 downto 0 do
      while !k >= t && ccw hull.(!k-2) hull.(!k-1) points.(i) <= 0 do
        decr k
      done;
      hull.(!k) <- points.(i);
      incr k
    done;
    let result = Array.make (!k + 1) hull.(0) in
    for i = 0 to !k - 1 do result.(i) <- hull.(i) done;
    result
end

let () =
  let p = [(1, 1); (3, 3); (9, 1); (12, 4); (9, 7); (1, 7)]
          |> List.map (fun (x, y) -> point(float_of_int x, float_of_int y))
          |> Polygon.of_points in

  printf "Perimeter of polygon = %.2f\n" (Polygon.perimeter p);
  printf "Area of polygon = %.2f\n" (Polygon.area p);
  printf "Area of polygon = %.2f\n" (Polygon.area_alternative p);
  printf "Is convex = %b\n" (Polygon.is_convex p);

  (* the positions of P6 and P7 w.r.t the polygon
  7 P5--------------P4
  6 |                  \
  5 |                    \
  4 |   P7                P3
  3 |   P1___            /
  2 | / P6    \ ___    /
  1 P0              P2
  0 1 2 3 4 5 6 7 8 9 101112 *)

  let p6 = point(3., 2.) in
  printf "Point P6 is inside this polygon = %b\n"
    (Polygon.in_polygon p p6);
  let p7 = point(3., 4.) in
  printf "Point P7 is inside this polygon = %b\n"
    (Polygon.in_polygon p p7);
  
  (* cutting the original polygon based on line P[2] -> P[4] (get the left side)
  7 P5--------------P4
  6 |               |  \
  5 |               |    \
  4 |               |     P3
  3 |   P1___       |    /
  2 | /       \ ___ |  /
  1 P0              P2
  0 1 2 3 4 5 6 7 8 9 101112
  new polygon (notice the index are different now):
  7 P4--------------P3
  6 |               |
  5 |               |
  4 |               |
  3 |   P1___       |
  2 | /       \ ___ |
  1 P0              P2
  0 1 2 3 4 5 6 7 8 9 *)

  let p = Polygon.cut_polygon p (point(9., 1.)) (point(9., 7.)) in
  printf "Perimeter of polygon = %.2f\n" (Polygon.perimeter p);
  printf "Area of polygon = %.2f\n" (Polygon.area p);

  (* running convex hull of the resulting polygon (index changes again)
  7 P3--------------P2
  6 |               |
  5 |               |
  4 |   P7          |
  3 |               |
  2 |               |
  1 P0--------------P1
  0 1 2 3 4 5 6 7 8 9 *)

  let p = Polygon.convex_hull (Polygon.points p) in
  printf "Perimeter of polygon = %.2f\n" (Polygon.perimeter p);
  printf "Area of polygon = %.2f\n" (Polygon.area p);
  printf "Is convex = %b\n" (Polygon.is_convex p);
  printf "Point P6 is inside this polygon = %b\n" (Polygon.in_polygon p p6);
  printf "Point P7 is inside this polygon = %b\n" (Polygon.in_polygon p p7)
