<?php
class PHP_Job
{
	public function perform()
	{
		var_dump($this->args);
        	fwrite(STDOUT, 'Start job! -> ');
		sleep(120);
		fwrite(STDOUT, 'Job ended!' . PHP_EOL);
	}
}

class My_job
{
	public function perform()
	{
		fwrite(STDOUT,"this is my job");
	}
}
