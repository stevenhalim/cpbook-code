(* Sharing Chocolate *)
open Scanf
open Printf

let twoPow x = 1 lsl x
let bitOn s x = s land twoPow x <> 0
let setBitOn s x = s lor twoPow x
let getbit s x = (s lsr x) land 1

let n = ref 0
let num_pieces = Array.make 16 0
let area = Array.make 65536 (-1)
let memo = Hashtbl.create 100

let count_area s =
  let ret = ref 0 in
  for i = 0 to !n-1 do
    if bitOn s i then begin
      ret := !ret + num_pieces.(i);
    end
  done;
  !ret

let getOnBits s =
  let rec helper acc i =
    if i < 0 then acc
    else if bitOn s i then helper (i :: acc) (i-1)
    else helper acc (i-1)
  in
  helper [] (!n-1)
;;

let rec dp w s =
  let open Hashtbl in
  if mem memo (w, s) then find memo (w, s)
  else begin
    let a = area.(s) in
    let h = a / w in
    if w = 0 || a mod w <> 0 then begin
      add memo (w, s) false;
      false
    end
    else if mem memo (h, s) then begin
      let ret = find memo (h, s) in
      add memo (w, s) ret;
      ret
    end
    else (
      let bit = Array.of_list (getOnBits s) in
      let l = Array.length bit in
      if l = 1 then begin
        add memo (w, s) true;
        true
      end
      else begin
          let last = twoPow (l-1) - 1 in
          let rec try_using t =
            if t = last then false
            else begin
              let s1 = ref (setBitOn 0 bit.(l-1)) in
              let s2 = ref 0 in
              for k = 0 to l-2 do 
                if bitOn t k then s1 := setBitOn !s1 bit.(k) else s2 := setBitOn !s2 bit.(k)
              done;
              let op1 = dp w !s1 && dp w !s2 in
              let op2 = dp h !s1 && dp h !s2 in
              if op1 || op2 then true else try_using (t+1)
            end
          in
          let ret = try_using 0 in
          add memo (w, s) ret;
          ret
        end
      )
    end

let () =
  let case = ref 1 in
  let rec solve () =
    scanf "%d" (fun k ->
      n := k;
      if !n <> 0 then begin
        scanf "\n%d %d\n" (fun x y ->
          scanf "%d" (fun z -> num_pieces.(0) <- z);
          for i = 1 to !n-1 do scanf " %d" (fun z -> num_pieces.(i) <- z) done;
          scanf "\n" ();
          let target = (twoPow !n) -1 in
          Array.fill area 0 65536 (-1);
          for i = 0 to target do area.(i) <- count_area i done;
          Hashtbl.reset memo;
          let str = if area.(target) <> x * y || not (dp y target) then "No\n" else "Yes\n" in
          printf "Case %d: %s" !case str;
          incr case;
          solve ()
        )
      end
    )
  in 
  solve ()


