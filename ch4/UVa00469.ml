open Scanf
open Printf

let solve () =
  let grid = ref [] in
  let line = ref "" in
  let _ = read_line () in
  let rec read_grid () =
    line := read_line ();
    if !line.[0] = 'L' || !line.[0] = 'W' then begin
      grid := Bytes.of_string !line :: !grid;
      read_grid ()
    end else () in
  read_grid ();

  let grid = !grid |> List.rev |> Array.of_list in
  let n, m = Array.length grid, Bytes.length grid.(0) in
  let rec flood_fill r c x y =
    if r < 0 || r >= n || c < 0 || c >= m then 0 else
    if Bytes.get grid.(r) c <> x then 0 else begin
      Bytes.set grid.(r) c y;
      [(1, 0); (1, 1); (0, 1); (-1, 1); (-1, 0); (-1, -1); (0, -1); (1, -1)]
        |> List.fold_left (fun sum (dr, dc) ->
            sum + flood_fill (r + dr) (c + dc) x y
          ) 1
    end
  in

  let rec query () =
    let r, c = sscanf !line "%d %d" (fun x y -> (x - 1, y - 1)) in
    printf "%d\n" (flood_fill r c 'W' '.');
    let _ = flood_fill r c '.' 'W' in
    try
      line := read_line ();
      if !line = "" then ()
      else query ()
    with _ -> ()
  in
  query ()

let () =
  let tc = read_int () in
  for _ = 1 to tc do solve () done
