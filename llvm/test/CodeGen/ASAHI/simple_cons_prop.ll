; RUN: opt -mtriple=asahi -passes=asahi-simple-cst-prop %s -S -o - | FileCheck %s
; RUN: opt -mtriple=asahi -asahi-simple-cst-prop --bugpoint-enable-legacy-pm %s -S -o - | FileCheck %s
; The command line for the legacy pass manager is likely going to be killed
; sooner than later. Here we abuse the bugpoint capabilities to get by.

; We should end up with the constant completely folded in the final phi.
; On one branch:
; (5 << 3) / 5 ==> 8
; On the other branch:
; (5 << 3) | 3855 ==> 3887
define i32 @foo(i32 noundef %arg) {
foo.bb:
  %i = shl i32 5, 3
  %i1 = icmp ne i32 %arg, 0
  br i1 %i1, label %foo.bb2, label %foo.bb4

foo.bb2:
  %i3 = sdiv i32 %i, 5
  br label %foo.bb6

foo.bb4:
  %i5 = or i32 %i, 3855
  br label %foo.bb6

foo.bb6:
  %.0 = phi i32 [ %i3, %foo.bb2 ], [ %i5, %foo.bb4 ]
  ret i32 %.0
}

; We should end up with the constant completely folded in the final phi.
; On one branch:
; (-1 << 3) /u 3 ==> 1431655762
; On the other branch:
; (-1 << 3) | 3855 ==> -1
define i32 @bar(i32 noundef %arg) {
bar.bb:
  %i = shl i32 -1, 3
  %i1 = icmp ne i32 %arg, 0
  br i1 %i1, label %bar.bb2, label %bar.bb4

bar.bb2:
  %i3 = udiv i32 %i, 3
  br label %bar.bb6

bar.bb4:
  %i5 = or i32 %i, 3855
  br label %bar.bb6

bar.bb6:
  %.0 = phi i32 [ %i3, %bar.bb2 ], [ %i5, %bar.bb4 ]
  %i7 = add i32 %.0, 1
  ret i32 %i7
}