<?php
class TV
{
	public function powderOn()
	{
		echo "I'm on";
	}

	public function powderOff()
	{
		echo "I'm off";
	}
}

interface Command
{
	public function exec();
}

class PowderonCommand
{
	public function __construct($tv)
	{
		$this->tv = $tv;
	}

	public function exec()
	{
		$this->tv->powderOn();
	}
}

class PowderoffCommand
{
	public function __construct($tv)
	{
		$this->tv = $tv;
	}

	public function exec()
	{
		$this->tv->powderOff();
	}
}

class Invoker
{
	public function __construct($command)
	{
		$this->command = $command;
	}

	public function runCommand()
	{
		$this->command->exec();
	}
}

// USE
$tv = new TV();
$powderon = new PowderonCommand($tv);
$invoker = new Invoker($powderon);
$invoker->runCommand();
