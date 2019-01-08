(* Editing a Book *)
open Scanf
open Printf

(* module IntMap = Map.Make(struct type t = int let compare = compare end) *)

let encode arr =
  let ret = ref 0 in
  let n = Array.length arr in
  for i = 0 to n-1 do 
    ret := (!ret * 10) + arr.(i)
  done;
  !ret

let decode x =
  let a = Array.make 9 0 and t = ref x in
  for i = 8 downto 0 do 
    a.(i) <- !t mod 10;
    t := !t / 10
  done;
  a

let bfs s nL dis refr =
  let q = Queue.create () in
  Queue.push s q;
  Hashtbl.reset dis;
  Hashtbl.add dis s 0;
  let l = ref 0 in
  let ret = ref 5 in
  while !l < nL && not (Queue.is_empty q) do 
    for qq = 1 to Queue.length q do 
      let u = Queue.take q in
      let a = decode u in
      for i = 0 to 8 do 
        for j = i to 8 do 
          let b = Array.(append (sub a 0 i) (sub a (j+1) (8-j))) in
          let b_len = Array.length b in
          let slice = Array.sub a i (j-i+1) in
          for k = 0 to b_len-1 do
            let c = Array.(concat [ sub b 0 k; slice; sub b k (b_len-k) ]) in
            let v = encode c in
            if !ret = 5 && Hashtbl.mem refr v
            then begin
              ret := !l + 1 + Hashtbl.find refr v;
            end;
            if not (Hashtbl.mem dis v) then begin
              Hashtbl.add dis v (!l+1);
              Queue.push v q
            end
          done
        done
      done
    done;
    incr l
  done;
  !ret

let () = 
  let d = Array.init 10 (fun _ -> Hashtbl.create 100) and case = ref 1 in
  for n = 1 to 9 do 
    let s = ref 0 in
    for i = 1 to n do 
      s := !s * 10 + i;
    done;
    ignore (bfs !s (min 2 n) d.(n) (Hashtbl.create 1));
  done;
  let rec solve () =
    scanf "%d" (fun n ->
      if n <> 0 then begin
        let a = Array.make n 0 in
        scanf "\n%d" (fun x -> a.(0) <- x);
        for i = 1 to n-1 do 
          scanf " %d" (fun x -> a.(i) <- x)
        done;
        scanf "\n" ();
        let v = encode a and res = ref 0 in
        if Hashtbl.mem d.(n) v
        then
          res := Hashtbl.find d.(n) v
        else begin
          res := bfs v 2 d.(0) d.(n)
        end;
        printf "Case %d: %d\n" !case !res;
        incr case;
        solve ()
      end
    )
  in
  solve ()
