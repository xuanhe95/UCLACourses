(defun which-line()
  "Print the current buffer line number and the total line number"
  (interactive)
  (setq n (what-line))
  (save-excursion
    (save-restriction
      (setq numline (count-lines (point-min) (point-max)))
      (if (= (point-min) (point-max))
	  (setq numline 0)
	(if (/= 10 (char-before (point-max)))
	    (setq numline (1- numline))
	  )
	)
      (message "%s of %d" n numline)
      )
    )
  )
