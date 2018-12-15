module UnionFind = struct
  type t =
    { parent: int array;
      rank: int array;
      size: int array;
      num_sets: int ref;
    }
  
  let create n =
    { parent  = Array.init n (fun x -> x);
      rank    = Array.make n 0;
      size    = Array.make n 1;
      num_sets = ref n;
    }
  
  let find { parent } u =
    let rec aux u =
      if parent.(u) = u then u
      else begin
        parent.(u) <- aux parent.(u);
        parent.(u)
      end
    in aux u
  
  let is_same_set dsu u v = find dsu u = find dsu v

  let union dsu u v =
    let link x p =
      dsu.parent.(x) <- p;
      dsu.size.(p) <- dsu.size.(p) + dsu.size.(x);
      if dsu.rank.(x) = dsu.rank.(p) then
        dsu.rank.(p) <- dsu.rank.(p) + 1
    in
    let pu, pv = find dsu u, find dsu v in
    if pu = pv then ()
    else begin
      decr dsu.num_sets;
      if dsu.rank.(pu) > dsu.rank.(pv) then link pv pu
      else link pu pv
    end
  
  let num_disjoint_sets { num_sets } = !num_sets

  let size_of_set dsu u = dsu.size.(find dsu u)
end


open Printf

let () =
  let open UnionFind in
  let dsu = create 5 in
  let print_nsets () = printf "%d\n" (num_disjoint_sets dsu) in
  print_nsets();
  [0, 1; 2, 3; 4, 3] |> List.iter (fun (u, v) ->
    union dsu u v;
    print_nsets()
  );
  [0, 3; 4, 3] |> List.iter (fun (u, v) ->
    printf "isSameSet(%d, %d) = %b\n" u v (is_same_set dsu u v)
  );
  let print_all () = List.init 5 (fun x -> x) |> List.iter (fun u ->
    printf "findSet(%d) = %d, sizeOfSet(%d) = %d\n"
      u (find dsu u) u (size_of_set dsu u)) in
  print_all();
  union dsu 0 3;
  print_nsets();
  print_all()
