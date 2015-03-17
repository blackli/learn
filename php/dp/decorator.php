<?php

interface Subject
{
	public function play();
}

abstract class Decorator implements Subject
{
	protected $decoratory = NULL;
	public function __construct(Subject $decorator)
	{
		$this->decorator = $decorator;
	}
}

class Phone implements Subject
{
	public function play()
	{
		echo "I'm phone" . PHP_EOL;
	}
}

class PhoneCell extends Decorator
{
	public function play() 
	{
		$this->decorator->play();
		echo "I have shell" . PHP_EOL;
	}
}

class PhoneSkin extends Decorator
{
	public function play() 
	{
		$this->decorator->play();
		echo "I have skin" . PHP_EOL;
	}
}

// USE
$phone = new Phone();
$phone = new PhoneCell($phone);
$phone = new PhoneSkin($phone);
$phone->play();
