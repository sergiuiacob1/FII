import com.jcraft.jsch.*;

import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Path;

/**
 * Uploads a local file to a remote host.
 */
class CopyToRemoteHost {

    /** Session to run commands */
    private Session session;

    /**
     * Creates a session to the remote host with the provided username and password data. Ignores certificates.
     * @param host remote host
     * @param user login name
     * @param pass password
     */
    CopyToRemoteHost(String host, String user, String pass) throws JSchException {
        this.session = createSession(host, user, pass);
    }

    /**
     * Creates a session from the provided connection data. The certificate is ignored when creating the session!
     * @param host remote host
     * @param user login name
     * @param pass password
     * @return SSH session
     */
    private Session createSession(String host, String user, String pass) throws JSchException {
        // Ignore certificate
        java.util.Properties config = new java.util.Properties();
        config.put("StrictHostKeyChecking", "no");

        // Create session
        JSch jsch = new JSch();
        Session session = jsch.getSession(user, host, 22);
        session.setConfig(config);
        session.setPassword(pass);
        return session;
    }

    /**
     * Copies the local file to the remote path.
     * @param srcPath path to local file
     * @param dstPath target path
     */
    void cp(Path srcPath, String dstPath) throws JSchException, IOException, SftpException {
        // This basically comes from JSch examples
        session.connect();
        ChannelSftp channel = (ChannelSftp) session.openChannel("sftp");
        channel.connect();
        // Assume the target is a path and the target file name will be the source file name
        String targetPath = dstPath;
        String targetFile = srcPath.getFileName().toString();
        try {
            channel.cd(dstPath);
        } catch (SftpException e) {
            // Target does not exist
            int lastIndexOf = targetPath.lastIndexOf('/');
            // target can also be only a file name
            if (lastIndexOf > -1) {
                targetFile = targetPath.substring(lastIndexOf + 1);
                targetPath = targetPath.substring(0, lastIndexOf + 1);
                channel.cd(targetPath);
            }
        }
        try {
            channel.put(new FileInputStream(srcPath.toFile()), targetFile, ChannelSftp.OVERWRITE);
        } finally {
            channel.exit();
            session.disconnect();
        }
    }
}