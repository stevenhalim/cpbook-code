open Printf
open Scanf

let () =
  try
    while true do
      let n, m = scanf "%d %d\n" (fun x y -> x, y) in
      if n = 0 && m = 0 then raise Exit;
      let dragon = Array.init n (fun _ -> scanf "%d\n" (fun x -> x)) in
      Array.sort compare dragon;
      let knight = Array.init m (fun _ -> scanf "%d\n" (fun x -> x)) in
      Array.sort compare knight;
      let gold = ref 0 in
      let d = ref 0 in
      let k = ref 0 in
      begin
        try
          while !d < n && !k < m do
            while !k < m && dragon.(!d) > knight.(!k) do k := !k+1 done;
            if !k = m then raise Exit;
            gold := !gold + knight.(!d);
            d := !d+1; k := !k+1;
          done
        with Exit -> ()
      end;
      if !d = n then printf "%d\n" !gold
      else printf "Loowater is doomed!\n"
    done
  with Exit -> ()
