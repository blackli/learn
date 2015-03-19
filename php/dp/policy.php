<?php
interface Encode
{
	public function exec($data);
}

class Json implements Encode
{
	public function exec($data)
	{
		return json_encode($data);
	}
}

class Api 
{
	public function setEncode(Encode $method)
	{
		$this->method = $method;
	}

	public function getFunc()
	{
		$data = array();
		return $this->method->exec($data);
	}
}

// USE
$api = new Api();
$api->setEncode(new Json());
echo $api->getFunc();
