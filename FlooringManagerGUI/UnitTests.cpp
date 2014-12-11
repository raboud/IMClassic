#include "stdafx.h"
#include "UnitTests.h"


UnitTests::UnitTests(void)
{

}

bool UnitTests::TestSendEmail()
{
	CString errorMessage;
	bool sendSuccess = CGlobals::SendEmail("dan.bartram@gmail.com, dan.bartram@custom-installs.com", "dbartram@custom-installs.com", "falcon...900", "", "dan.bartram@gmail.com", "TestSendEmail", "This is a test email from IMC.", errorMessage);

	return sendSuccess;
}

UnitTests::~UnitTests(void)
{
}
