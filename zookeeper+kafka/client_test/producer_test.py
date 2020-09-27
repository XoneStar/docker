# --coding:utf-8--

import sys

from confluent_kafka import Producer

conf = {'bootstrap.servers': 'x.x.x.x:9092',
        'security.protocol': 'ssl',
        'ssl.ca.location': 'ca-cert',
        'ssl.certificate.location': 'xxx.pem',
        'ssl.key.location': 'xxx.key',
        'ssl.key.password': 'xxx'
        }

# Create Producer instance
p = Producer(**conf)


def delivery_callback(err, msg):
    if err:
        sys.stderr.write('%% Message failed delivery: %s\n' % err)
    else:
        sys.stderr.write('%% Message delivered to %s [%d] @ %o\n' %
                         (msg.topic(), msg.partition(), msg.offset()))


# Read lines from stdin, produce each line to Kafka
for line in ['test1', 'test2', 'test3']:
    try:
        # Produce line (without newline)
        p.produce('test', line.rstrip(), callback=delivery_callback)

    except BufferError:
        sys.stderr.write('%% Local producer queue is full (%d messages awaiting delivery): try again\n' %
                         len(p))

    # Serve delivery callback queue.
    # NOTE: Since produce() is an asynchronous API this poll() call
    #       will most likely not serve the delivery callback for the
    #       last produce()d message.
    p.poll(0)

# Wait until all messages have been delivered
sys.stderr.write('%% Waiting for %d deliveries\n' % len(p))
p.flush()
