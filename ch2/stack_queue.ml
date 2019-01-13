(* This source code is not as complete as ch2/stack_queue.ml *)

open Printf

let () =
  let s = Stack.create () in
  let q = Queue.create () in

  printf "%B\n" (Stack.is_empty s);
  printf "==================\n";
  Stack.push 'a' s;
  Stack.push 'b' s;
  Stack.push 'c' s;

  printf "%c\n" (Stack.top s);
  Stack.pop s |> ignore;
  printf "%c\n" (Stack.top s);
  printf "%B\n" (Stack.is_empty s);
  printf "==================\n";

  printf "%B\n" (Queue.is_empty q);
  printf "==================\n";
  while (not (Stack.is_empty s)) do
    Queue.push (Stack.pop s) q;
  done;
  Queue.push 'z' q;
  printf "%c\n" (Queue.top q);

  printf "==================\n";
  while (not (Queue.is_empty q)) do
    printf "%c\n" (Queue.pop q);
  done;
