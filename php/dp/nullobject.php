<?php
interface Params
{
	public function getName();
}

class NullParams implements Params
{
	public function getName()
	{
		echo '';
	}
}

class ValidParams implements Params
{
	public function getName()
	{
		echo 'I have name' . PHP_EOL;
	}
}

// USE
$params = new ValidParams();
$params->getName();

$params = new NullParams();
$params->getName();
