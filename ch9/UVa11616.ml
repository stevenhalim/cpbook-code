(* Roman Numerals *)

open Printf
open Scanf

module CMap = Map.Make (struct
    type t = char
    let compare = compare
  end)

let ator a =
  let cvt = [                                     (* from large to small *)
    1000,"M"; 900,"CM"; 500,"D"; 400,"CD"; 100,"C"; 90,"XC";
    50,"L"; 40,"XL"; 10,"X"; 9,"IX"; 5,"V"; 4,"IV"; 1,"I"
  ] in
  let buf = Buffer.create 8 in
  let a = ref a in
  cvt |> List.iter (fun (n, s) ->
      while !a >= n do
        bprintf buf "%s" s;
        a := !a - n
      done
    );
  Buffer.contents buf

let rtoa r =
  let rtoa = [
    'I',1; 'V',5; 'X',10; 'L',50;
    'C',100; 'D',500; 'M',1000
  ] |> List.to_seq |> CMap.of_seq in
  let value = ref 0 in
  for i = 0 to String.length r - 1 do
    if i < String.length r - 1 && CMap.find r.[i] rtoa < CMap.find r.[i+1] rtoa then  (* check next char first *)
      value := !value - CMap.find r.[i] rtoa
    else
      value := !value + CMap.find r.[i] rtoa
  done;
  !value

let () =
  try
    while true do
      let str = scanf "%s\n" (fun x -> x) in
      try
        let a = sscanf str "%d" (fun x -> x) in
        printf "%s\n" (ator a)               (* Arabic to Roman Numerals *)
      with Scan_failure _ ->
        printf "%d\n" (rtoa str)             (* Roman to Arabic Numerals *)
    done
  with End_of_file -> ()
