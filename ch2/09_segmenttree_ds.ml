open Printf

module type Semigroup = sig
  type t
  val op: t -> t -> t
end

module SegmentTree(Sg: Semigroup) = struct
  type elt = Sg.t

  type tree =
    { v: elt;
      ch: (tree * tree) option;
    }

  type t =
    { n: int;
      st: tree;
    }

  let init n f =
    let rec aux l r =
      if r = l + 1 then
        {v = f l; ch = None}
      else
        let m = (l + r) / 2 in
        let left = aux l m in
        let right = aux m r in
        { v = Sg.op left.v right.v;
          ch = Some (left, right);
        }
    in
    { n;
      st = aux 0 n;
    }

  let rmq i j t =
    let j = j + 1 in
    let rec aux l r st =
      if i >= r || j <= l then None
      else if i <= l && j >= r then Some st.v
      else match st.ch with
        | None -> failwith "Impossible"
        | Some (left, right) ->
          let m = (l + r) / 2 in
          let v1 = aux l m left in
          let v2 = aux m r right in
          match v1, v2 with
          | None, _ -> v2
          | _, None -> v1
          | Some v1', Some v2' -> Some (Sg.op v1' v2')
    in
    match aux 0 t.n t.st with
    | None -> raise (failwith "Empty range")
    | Some v -> v

  let update i v t =
    let rec aux l r st =
      if i >= r || i < l then st
      else match st.ch with
        | None -> {st with v}
        | Some (left, right) ->
          let m = (l + r) / 2 in
          let st1 = aux l m left in
          let st2 = aux m r right in
          { v = Sg.op st1.v st2.v;
            ch = Some (st1, st2);
          }
    in
    {t with st = aux 0 t.n t.st}
end

let () =
  let a = [|18; 17; 13; 19; 15; 11; 20|] in
  let module ST = SegmentTree (struct
      type t = int
      let op x y = if a.(x) <= a.(y) then x else y
    end) in
  let st = ref (ST.init (Array.length a) (fun i -> i)) in

  printf "              idx    0, 1, 2, 3, 4, 5, 6\n";
  printf "              A is {18,17,13,19,15,11,20}\n";
  printf "RMQ(1, 3) = %d\n" (ST.rmq 1 3 !st);             (* answer = index 2 *)
  printf "RMQ(4, 6) = %d\n" (ST.rmq 4 6 !st);             (* answer = index 5 *)
  printf "RMQ(3, 4) = %d\n" (ST.rmq 3 4 !st);             (* answer = index 4 *)
  printf "RMQ(0, 0) = %d\n" (ST.rmq 0 0 !st);             (* answer = index 0 *)
  printf "RMQ(0, 1) = %d\n" (ST.rmq 0 1 !st);             (* answer = index 1 *)
  printf "RMQ(0, 6) = %d\n" (ST.rmq 0 6 !st);             (* answer = index 5 *)

  printf "              idx    0, 1, 2, 3, 4, 5, 6\n";
  printf "Now, modify A into {18,17,13,19,15,99,20}\n";
  a.(5) <- 99;
  st := ST.update 5 5 !st;
  printf("These values do not change\n");
  printf "RMQ(1, 3) = %d\n" (ST.rmq 1 3 !st);                            (* 2 *)
  printf "RMQ(3, 4) = %d\n" (ST.rmq 3 4 !st);                            (* 4 *)
  printf "RMQ(0, 0) = %d\n" (ST.rmq 0 0 !st);                            (* 0 *)
  printf "RMQ(0, 1) = %d\n" (ST.rmq 0 1 !st);                            (* 1 *)
  printf "These values change\n";
  printf "RMQ(0, 6) = %d\n" (ST.rmq 0 6 !st);  (* answer changes = index 5->2 *)
  printf "RMQ(4, 6) = %d\n" (ST.rmq 4 6 !st);  (* answer changes = index 5->4 *)
  printf "RMQ(4, 5) = %d\n" (ST.rmq 4 5 !st);  (* answer changes = index 5->4 *)
