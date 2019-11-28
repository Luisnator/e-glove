var noble = require('noble');
var serviceUUIDs = ["d9c0fc91-b16e-4517-94a5-65eb152ccd44"]; // default: [] => all
var allowDuplicates = false; // default: false

noble.startScanning(serviceUUIDs, allowDuplicates); // particular UUID's
peripheral.connect();