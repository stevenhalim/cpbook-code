open Printf

let () =
  (* as in Figure in HLD section, not yet rooted *)
  let n = 19 in
  let al = Array.make n [||] in                  (* undirected tree *)
  al.(0) <- [|1; 2; 3|];
  al.(1) <- [|0; 4|];
  al.(2) <- [|0; 5; 6; 7|];
  al.(3) <- [|0; 8|];
  al.(4) <- [|1; 9; 10|];
  al.(5) <- [|2|];
  al.(6) <- [|2|];
  al.(7) <- [|2; 11; 12|];
  al.(8) <- [|3|];
  al.(9) <- [|4|];
  al.(10) <- [|4; 13|];
  al.(11) <- [|7; 14|];
  al.(12) <- [|7; 15|];
  al.(13) <- [|10|];
  al.(14) <- [|11; 16|];
  al.(15) <- [|12; 17; 18|];
  al.(16) <- [|14|];
  al.(17) <- [|15|];
  al.(18) <- [|15|];

  let par = Array.make n (-1) in
  let heavy = Array.make n (-1) in

  let rec heavy_light x =                        (* DFS traversal on tree *)
    let size = ref 1 in
    let max_child_size = ref 0 in
    al.(x) |> Array.iter (fun y ->               (* edge x->y *)
        if y <> par.(x) then (                   (* avoid cycle in a tree *)
          par.(y) <- x;
          let child_size = heavy_light y in      (* recurse *)
          if child_size > !max_child_size then (
            max_child_size := child_size;
            heavy.(x) <- y                       (* y is x's heaviest child *)
          );
          size := !size + child_size
        )
      );
    !size
  in
  heavy_light 0 |> ignore;

  let group = Array.make n (-1) in

  let rec decompose x p =
    group.(x) <- p;                              (* x is in group p *)
    al.(x) |> Array.iter (fun y ->               (* edge x->y *)
        if y <> par.(x) then (                   (* avoid cycle in a tree *)
          if y = heavy.(x) then
            decompose y p                        (* y is in group p *)
          else
            decompose y y                        (* y is in new group y *)
        )
      )
  in
  decompose 0 0;

  for i = 0 to n - 1 do
    printf "%2d, parent = %2d, heaviest child = %2d, belong to heavy-paths group = %d\n" i par.(i) heavy.(i) group.(i);
  done
