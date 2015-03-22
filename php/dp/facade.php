<?php
class Api
{
	public function __construct($hello, $world)
	{
		$this->hello = $hello;
		$this->world = $world;
	}

	public function helloworld()
	{
		$this->hello->hello();
		$this->world->world();
	}
}

class A
{
	public function hello()
	{
		echo 'Hello' . PHP_EOL;
	}
}

class B
{
	public function world()
	{
		echo 'World' . PHP_EOL;
	}
}

// USE
$a = new A();
$b = new B();
$api = new Api($a, $b);
$api->helloworld();
