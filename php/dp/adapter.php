<?php
class Foo
{
	public function __construct($adapter)
	{
		$this->adapter = $adapter;
	}

	public function doSomething()
	{
		$this->adapter->dosmt();
	}
}

interface Adapter
{
	public function dosmt();
}

class A implements Adapter
{
	public function dosmt()
	{
		echo 'hello';
	}
}

class B implements Adapter
{
	public function dosmt()
	{
		echo 'world';
	}
}

$a = new Foo(new A());
$a->doSomething();

$b = new Foo(new B());
$b->doSomething();


