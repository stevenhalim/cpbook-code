(* This source code is not as complete as list.cpp *)

open Printf

let () =
  let s = Stack.create () in
  let q = Queue.create () in

  printf "%B\n" (Stack.is_empty s);       (* currently s is empty, true *)
  printf "==================\n";
  Stack.push 'a' s;
  Stack.push 'b' s;
  Stack.push 'c' s;
  (* stack is LIFO, thus the content of s is currently like this:
   * c <- top
   * b
   * a *)
  printf "%c\n" (Stack.top s);                            (* output 'c' *)
  Stack.pop s |> ignore;                                 (* pop topmost *)
  printf "%c\n" (Stack.top s);                            (* output 'b' *)
  printf "%B\n" (Stack.is_empty s);  (* currently s is not empty, false *)
  printf "==================\n";

  printf "%B\n" (Queue.is_empty q);       (* currently q is empty, true *)
  printf "==================\n";
  while (not (Stack.is_empty s)) do   (* stack s still has 2 more items *)
    Queue.push (Stack.pop s) q;            (* enqueue 'b', and then 'a' *)
  done;
  Queue.push 'z' q;                                (* add one more item *)
  printf "%c\n" (Queue.top q);                            (* prints 'b' *)

  (* output 'b', 'a', then 'z' (until queue is empty), according to the insertion order above *)
  printf "==================\n";
  while (not (Queue.is_empty q)) do
    printf "%c\n" (Queue.peek q);               (* take the front first *)
    Queue.pop q |> ignore            (* before popping (dequeue-ing) it *)
  done;
