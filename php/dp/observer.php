<?php
interface Observable
{
	public function addObserver(Observer $observer);
	public function rmObjserver(Observer $observer);
	public function notifyObservers($args);
}

interface Observer
{
	public function update($args);
}

class Teather implements Observable
{
	private $observers = array();

	public function addObserver(Observer $observer)
	{
		array_push($this->observers, $observer);
	}

	public function rmObjserver(Observer $observer)
	{
		//
	}

	public function notifyObservers($args = array())
	{
		foreach ($this->observers as $observer)
			$observer->update($args);
	}
}

class StudentA implements Observer
{
	public function update($args)
	{
		echo 'I\'m student A' . PHP_EOL;
	}
}

class StudentB implements Observer
{
	public function update($args)
	{
		echo 'I\'m student B' . PHP_EOL;
	}
}

// USE
$studentA = new StudentA;
$studentB = new StudentB;
$teacher = new Teather;
$teacher->addObserver($studentA);
$teacher->addObserver($studentB);
$teacher->notifyObservers();
