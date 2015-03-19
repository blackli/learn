<?php
class Proxy
{
	public function __construct()
	{
		$this->your = new Your();
	}

	function getYourBag()
	{
		$this->your->bag();
	}
}

class Your
{
	public function bag()
	{
		echo 'I get your bag';
	}
}

$proxy = new Proxy();
$proxy->getYourBag();
