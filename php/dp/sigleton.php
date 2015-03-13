<?php
class Foo
{
	static $instance;

	private function __construct() {}
	private function __clone() {}
	private function __wakeup() {}

	static public function getInstance()
	{
		if (!self::$instance instanceof self)
			self::$instance = new self();

		return self::$instance;
	}
}

// USE
$bar = Foo::getInstance();
