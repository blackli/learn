<?php
interface Status
{
	public function dosmt();
}

class StatusA implements Status
{
	public function dosmt()
	{
		echo 'hello' . PHP_EOL;
	}
}

class StatusB implements Status
{
	public function dosmt()
	{
		echo 'world' . PHP_EOL;
	}
}

// 自动选择状态
class Client
{
	public function smtHappen()
	{
		$this->status = new StatusA();
	}

	public function dosmt()
	{
		$this->status->dosmt();
	}
}
