import iotkit;

print 'iotkit library version:', iotkit.iotkit_get_version();

response = iotkit.getAccountActivationCode();
print 'Response received: ', response;
