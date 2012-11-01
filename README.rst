Usage
=======
.. code::

  defer ( <exps | statements> );
  defer ( <exps | statements> ) namely ( <name> );

Example
========
.. code::

  if ((fd = mkstemp(buf)) < 0)
	return -1;
  defer(close(fd); unlink(buf));  // auto-close, auto-delete when scope exits.

  defer(vec_.pop_back()) namely(undoer);
  vec_.push_back(x);
  /* something may fail */
  undoer.dismiss();               // strong guarantee

See also
==========
.. [1] C++11（及现代C++风格）和快速迭代式开发
  http://mindhacks.cn/2012/08/27/modern-cpp-practices/

.. [2] Generic: Change the Way You Write Exception-Safe Code ― Forever
  http://www.drdobbs.com/cpp/generic-change-the-way-you-write-excepti/184403758
