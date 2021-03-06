require 'em-websocket'

EM.run {
  EM::WebSocket.run(:host => "127.0.0.1", :port => 9002) do |ws|
    ws.onopen { |handshake|
      puts "WebSocket connection open"

      # Access properties on the EM::WebSocket::Handshake object, e.g.
      # path, query_string, origin, headers

      # Publish message to the client
      ws.send "Hello Client"
    }

    ws.onclose { puts "Connection closed" }

    ws.onmessage { |msg|
      puts "#{msg}"
    }
  end
}